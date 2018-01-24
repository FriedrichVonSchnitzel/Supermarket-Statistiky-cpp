#ifndef DATASTATISTICS_H
#define DATASTATISTICS_H

#include <QTextStream>
#include <QMetaType>

class DataStatistics
{
	unsigned int m_customers;
	float m_revenue, m_expenses;

public:
	DataStatistics(unsigned int a_customers = 0, float a_revenue = 0, float a_expenses = 0);

	unsigned int customers() const;
	void setCustomers(unsigned int a_customers);
	void addCustomer(); // Add one customer

	float average() const;

	float revenue() const;
	void setRevenue(float a_revenue);
	void addRevenue(float a_revenue); // Add revenue, use negative value to substract

	float expenses() const;
	void setExpenses(float a_expenses);
	void addExpenses(float a_expenses); // Add expenses, use negative value to substract

	float result() const;

	void addDataStatistics(const DataStatistics &other); // Add values of another DataStatistics class to this one

private:
	void addCustomers(unsigned int a_customers); // Add customers
};

Q_DECLARE_METATYPE(DataStatistics)

#endif // DATASTATISTICS_H
