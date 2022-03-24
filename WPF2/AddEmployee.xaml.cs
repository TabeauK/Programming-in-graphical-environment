using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Lab2
{
    /// <summary>
    /// Logika interakcji dla klasy AddEmployee.xaml
    /// </summary>
    public partial class AddEmployee : Window
    {
        public MainWindow.Employee employee;

        private MainWindow window;


        public AddEmployee(MainWindow main)
        {
            window = main;
            employee = new MainWindow.Employee("", "", "Male", DateTime.Today.AddYears(-30), "", 5000, MainWindow.Currency.PLN, MainWindow.Role.Worker);
            this.DataContext = employee;
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            window.AddNewEmployee(employee);
            this.Close();
        }
    }

}
