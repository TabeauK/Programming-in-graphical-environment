using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Lab2
{
    public partial class MainWindow : Window
    {
        public enum Currency { PLN, USD, EUR, GBP, NOK }
        public enum Role { Worker, SeniorWorker, IT, Manager, Director, CEO }
        public class Employee : INotifyPropertyChanged
        {
            private string firstName;
            public string FirstName
            {
                get { return firstName; }
                set { firstName = value; PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("FirstName")); }
            }
            private string lastName;
            public string LastName
            {
                get { return lastName; }
                set { lastName = value; PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("LastName")); }
            }
            private string sex;
            public string Sex
            {
                get { return sex; }
                set { sex = value; PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Sex")); }
            }
            private DateTime birthDate;
            public DateTime BirthDate
            {
                get { return birthDate; }
                set { birthDate = value; PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("BirthDate")); }
            }

            private string birthCountry;
            public string BirthCountry
            {
                get { return birthCountry; }
                set { birthCountry = value; PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("BirthCountry")); }
            }

            private int salary;
            public int Salary
            {
                get { return salary; }
                set { salary = value; PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Salary")); }
            }

            private Currency salaryCurrency;
            public Currency SalaryCurrency
            {
                get { return salaryCurrency; }
                set { salaryCurrency = value; PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("SalaryCurrency")); }
            }

            private Role companyRole;
            public Role CompanyRole
            {
                get { return companyRole; }
                set { companyRole = value; PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("CompanyRole")); }
            }

            public Employee(string firstName, string lastName, string sex, DateTime birthDate, string birthCountry, int salary, Currency salaryCurrency, Role companyRole)
            {
                FirstName = firstName;
                LastName = lastName;
                Sex = sex;
                BirthDate = birthDate;
                BirthCountry = birthCountry;
                Salary = salary;
                SalaryCurrency = salaryCurrency;
                CompanyRole = companyRole;
            }

            public event PropertyChangedEventHandler PropertyChanged;

            public string CSV()
            {
                return FirstName + ";" + LastName + ";" + Sex + ";" + BirthDate.ToString("dd.MM.yyyy") + ";" + BirthCountry + ";" + Salary + ";" + (int)SalaryCurrency + ";" + (int)CompanyRole;
            }
        }

    }
}