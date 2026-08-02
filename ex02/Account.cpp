/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozetlers <ozetlers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 01:13:02 by ozetlers          #+#    #+#             */
/*   Updated: 2026/08/02 03:46:15 by ozetlers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Reconstruction of the lost Account.cpp for GlobalBanksters United
// (42 CPP Module 00, exercise 02). The observable behaviour is pinned by the
// reference log 19920104_091532.log; the interface is pinned by the provided
// Account.hpp, which is not modified.
//
// ---------------------------------------------------------------------------
// Class-wide invariants and deliberate contract choices
// ---------------------------------------------------------------------------
// _nbAccounts serves TWO roles at once: it is the value returned by
//   getNbAccounts(), and it is the monotonic generator of _accountIndex. It is
//   therefore never decremented. Decrementing it in the destructor would let a
//   later account reuse a retired index.
//
// _totalAmount records the bank's cumulative position, not the sum of the
//   balances of the accounts that are currently alive. Like _nbAccounts, it is
//   not unwound by the destructor. Consequence: displayAccountsInfos() reports
//   historical figures once any account has been destroyed. This is
//   intentional, and is the reason the destructor below only logs.
//
// Ledger arithmetic is performed on int, as fixed by Account.hpp. Signed
//   integer overflow is undefined behaviour (C++98 [expr]/5) -- not wraparound
//   -- so the cumulative bank position must remain inside the range of int.
//   The class does not, and with this header cannot, check that.
//
// Account declares neither a copy constructor nor a copy-assignment operator,
//   so the compiler generates memberwise versions (C++98 12.8). A copy
//   duplicates _accountIndex, is never registered in the class-wide ledger,
//   and still logs ";closed" when it dies. The header cannot be changed, and
//   tests.cpp stores Accounts in a std::vector, which requires the type to
//   remain copyable -- so copies must simply not be made.

#include <ctime>
#include <iomanip>
#include <iostream>

#include "Account.hpp"

// ************************************************************************** //
//                        Static attributes definitions                       //
// ************************************************************************** //

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

// ************************************************************************** //
//                            Static member functions                         //
// ************************************************************************** //

int	Account::getNbAccounts( void )
{
	return ( Account::_nbAccounts );
}

int	Account::getTotalAmount( void )
{
	return ( Account::_totalAmount );
}

int	Account::getNbDeposits( void )
{
	return ( Account::_totalNbDeposits );
}

int	Account::getNbWithdrawals( void )
{
	return ( Account::_totalNbWithdrawals );
}

// Logs the bank-wide ledger. See the file header: after any destruction these
// figures are cumulative, not a snapshot of the accounts still alive.
void	Account::displayAccountsInfos( void )
{
	Account::_displayTimestamp();
	std::cout << "accounts:" << Account::getNbAccounts()
			  << ";total:" << Account::getTotalAmount()
			  << ";deposits:" << Account::getNbDeposits()
			  << ";withdrawals:" << Account::getNbWithdrawals()
			  << std::endl;
}

// Prints "[YYYYMMDD_HHMMSS] " on the standard output, without any newline.
// std::setw is consumed by the next formatted output, hence one per field;
// the fill character is sticky, hence it is saved and restored so that the
// caller's stream state is left exactly as it was found.
// std::localtime may return a null pointer; the sentinel keeps the field
// geometry intact so that a log reader never sees a truncated record.
void	Account::_displayTimestamp( void )
{
	std::time_t const	now = std::time( NULL );
	std::tm const		*date = std::localtime( &now );

	if ( date == NULL )
	{
		std::cout << "[00000000_000000] ";
		return ;
	}

	char const	previous_fill = std::cout.fill( '0' );

	std::cout << "[" << ( date->tm_year + 1900 )
			  << std::setw( 2 ) << ( date->tm_mon + 1 )
			  << std::setw( 2 ) << date->tm_mday
			  << "_"
			  << std::setw( 2 ) << date->tm_hour
			  << std::setw( 2 ) << date->tm_min
			  << std::setw( 2 ) << date->tm_sec
			  << "] ";
	std::cout.fill( previous_fill );
}

// ************************************************************************** //
//                          Constructor and destructor                        //
// ************************************************************************** //

// Registers a new account and logs its creation. The mem-initialiser list is
// evaluated before the constructor body (C++98 12.6.2), so _accountIndex takes
// the value _nbAccounts had *before* the increment below -- which is what makes
// the indices run 0, 1, 2, ... in creation order.
Account::Account( int initial_deposit ) :
	_accountIndex( Account::_nbAccounts ),
	_amount( initial_deposit ),
	_nbDeposits( 0 ),
	_nbWithdrawals( 0 )
{
	Account::_nbAccounts++;
	Account::_totalAmount += initial_deposit;

	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
			  << ";amount:" << this->_amount
			  << ";created" << std::endl;
}

// Logs the closure of the account. The bank-wide ledger is deliberately not
// unwound here; see the file header for why.
Account::~Account( void )
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
			  << ";amount:" << this->_amount
			  << ";closed" << std::endl;
}

// ************************************************************************** //
//                           Public member functions                          //
// ************************************************************************** //

// Credits `deposit` to this account and to the bank-wide totals, increments
// both deposit counters, and logs the transaction.
// Precondition: deposit >= 0. The class does not enforce it: a negative
// argument is applied verbatim, debiting the account while still counting as
// a deposit.
void	Account::makeDeposit( int deposit )
{
	int const	p_amount = this->checkAmount();

	this->_amount += deposit;
	this->_nbDeposits++;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;

	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
			  << ";p_amount:" << p_amount
			  << ";deposit:" << deposit
			  << ";amount:" << this->_amount
			  << ";nb_deposits:" << this->_nbDeposits
			  << std::endl;
}

// Debits `withdrawal` from this account when the balance covers it.
// On success: updates the account and the bank-wide totals, logs
//   ";withdrawal:<n>;amount:<n>;nb_withdrawals:<n>", and returns true.
// On refusal: leaves every counter and balance unchanged, logs
//   ";withdrawal:refused", and returns false.
// Precondition: withdrawal >= 0. The class does not enforce it: a negative
// argument passes the guard below and credits the account while still counting
// as a withdrawal.
bool	Account::makeWithdrawal( int withdrawal )
{
	int const	p_amount = this->checkAmount();

	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
			  << ";p_amount:" << p_amount
			  << ";withdrawal:";
	if ( p_amount < withdrawal )
	{
		std::cout << "refused" << std::endl;
		return ( false );
	}
	this->_amount -= withdrawal;
	this->_nbWithdrawals++;
	Account::_totalAmount -= withdrawal;
	Account::_totalNbWithdrawals++;

	std::cout << withdrawal
			  << ";amount:" << this->_amount
			  << ";nb_withdrawals:" << this->_nbWithdrawals
			  << std::endl;
	return ( true );
}

// Returns the current balance. Does not modify the object or the ledger.
int	Account::checkAmount( void ) const
{
	return ( this->_amount );
}

// Logs this account's own state. Does not modify the object or the ledger.
void	Account::displayStatus( void ) const
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
			  << ";amount:" << this->_amount
			  << ";deposits:" << this->_nbDeposits
			  << ";withdrawals:" << this->_nbWithdrawals
			  << std::endl;
}
