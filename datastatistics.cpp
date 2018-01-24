#include "datastatistics.h"

DataStatistics::DataStatistics(unsigned int a_customers, float a_revenue, float a_expenses)
	: m_customers(a_customers)
	, m_revenue(a_revenue)
	, m_expenses(a_expenses)
{}

unsigned int DataStatistics::customers() const
{
	return m_customers;
}

void DataStatistics::setCustomers(unsigned int a_customers)
{
	m_customers = a_customers;
}

void DataStatistics::addCustomer()
{
	m_customers++;
}

float DataStatistics::average() const
{
	return revenue() / customers();
}

float DataStatistics::revenue() const
{
	return m_revenue;
}

void DataStatistics::setRevenue(float a_revenue)
{
	m_revenue = a_revenue;
}

void DataStatistics::addRevenue(float a_revenue)
{
	m_revenue += a_revenue;
}

float DataStatistics::expenses() const
{
	return m_expenses;
}

void DataStatistics::setExpenses(float a_expenses)
{
	m_expenses = a_expenses;
}

void DataStatistics::addExpenses(float a_expenses)
{
	m_expenses += a_expenses;
}

float DataStatistics::result() const
{
	return revenue() - expenses();
}

void DataStatistics::addDataStatistics(const DataStatistics &other)
{
	addCustomers(other.customers());
	addRevenue(other.revenue());
	addExpenses(other.expenses());
}

void DataStatistics::addCustomers(unsigned int a_customers)
{
	m_customers += a_customers;
}
