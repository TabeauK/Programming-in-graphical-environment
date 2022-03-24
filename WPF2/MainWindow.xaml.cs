using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Lab2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        private class info
        {
            public ObservableCollection<Employee> Employees { get; set; }

            public string FirstLine;
            public string path;
            public bool Change;
            public AddEmployee window;
        }

        private info Info { get; set; }

        public MainWindow()
        {
            Info = new info() { Employees = new ObservableCollection<Employee>() };
            this.DataContext = Info;
            Info.Change = false;
            Info.Employees.CollectionChanged += Employees_CollectionChanged;
            InitializeComponent();
        }

        private void Employees_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            Info.Change = true;
        }

        public void Employee_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            Info.Change = true;
        }



        public void AddNewEmployee(Employee e)
        {
            e.PropertyChanged += Employee_PropertyChanged;
            Info.Employees.Add(e);
        }

        private void MyWindowClosing(object sender, CancelEventArgs e)
        {
            if (!(Info.window is null))
                Info.window.Close();
        }

    }
}
