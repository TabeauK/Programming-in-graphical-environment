using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Lab2
{

    public partial class MainWindow : Window
    {
        private void Down_Click(object sender, RoutedEventArgs e)
        {
            if (Info.Employees == null || Info.path == null || Info.Employees.Count <= 0 || Elist.SelectedIndex == -1 || Elist.SelectedIndex == Info.Employees.Count - 1)
            {
                return;
            }
            int index = Elist.SelectedIndex;
            var emp = Info.Employees[index];
            Info.Employees[index] = Info.Employees[index + 1];
            Info.Employees[index + 1] = emp;
            Elist.SelectedIndex = index + 1;

        }

        private void Up_Click(object sender, RoutedEventArgs e)
        {
            if (Info.Employees == null || Info.path == null || Info.Employees.Count <= 0 || Elist.SelectedIndex == -1 || Elist.SelectedIndex == 0)
            {
                return;
            }
            int index = Elist.SelectedIndex;
            var emp = Info.Employees[index];
            Info.Employees[index] = Info.Employees[index - 1];
            Info.Employees[index - 1] = emp;
            Elist.SelectedIndex = index - 1;
        }

        private void Add_Click(object sender, RoutedEventArgs e)
        {
            if (Info.Employees is null || Info.path==null)
                return;
            if(Info.window is null || !Info.window.IsVisible)
            {
                Info.window = new AddEmployee(this);
            }
            else
            {
                Info.window.WindowState = WindowState.Normal;
            }
            Info.window.WindowStartupLocation = WindowStartupLocation.CenterScreen;
            Info.window.Topmost = true;
            Info.window.Show();

        }

        private void Delete_Click(object sender, RoutedEventArgs e)
        {
            if(Info.Employees is null || Info.path==null || Info.Employees.Count==0 || Elist.SelectedIndex==-1)
            {
                return;
            }
            int index = Elist.SelectedIndex;
            Info.Employees[index].PropertyChanged -= Employee_PropertyChanged;
            Info.Employees.RemoveAt(index);
            Elist.SelectedIndex = -1;
        }
    }
}
