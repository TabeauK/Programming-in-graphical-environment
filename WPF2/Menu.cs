using Microsoft.Win32;
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

        private void SaveFile_Click(object sender, RoutedEventArgs e)
        {
            if (Info.path is null)
            {
                return;
            }
            Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog()
            {
                Filter = "CSV files| *.csv"
            };
            if (dlg.ShowDialog() == true)
            {
                Info.path = dlg.FileName;
                Save(Info.path);
            }

        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            Save(Info.path);
        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            if (Info.Change)
            {
                MessageBoxResult questionResult = MessageBox.Show("Do you want to save the changes?", "Warning", MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                if (questionResult == MessageBoxResult.Cancel || questionResult == MessageBoxResult.None)
                {
                    return;
                }
                else if (questionResult == MessageBoxResult.Yes)
                {
                    Save(Info.path);
                }
            }
            System.Windows.Application.Current.Shutdown();
        }

        private void Save(string path)
        {
            var Write = new System.IO.StreamWriter(path, false);
            Write.WriteLine(Info.FirstLine);
            foreach (var elem in Info.Employees)
            {
                Write.WriteLine(elem.CSV());
            }
            Write.Close();
            Info.Change = false;
        }


        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (Info.Change)
            {
                MessageBoxResult questionResult = MessageBox.Show("Do you want to save the changes?", "Warning", MessageBoxButton.YesNoCancel, MessageBoxImage.Question);
                if (questionResult == MessageBoxResult.Cancel || questionResult == MessageBoxResult.None)
                {
                    return;
                }
                else if (questionResult == MessageBoxResult.Yes)
                {
                    Save(Info.path);
                }
            }

            OpenFileDialog ofd = new OpenFileDialog
            {
                Filter = "Csv Files| *.csv"
            };
            if (ofd.ShowDialog() == true)
            {
                Info.path = ofd.FileName;
            }
            else
            {
                return;
            }

            Info.Employees.Clear();
            string[] emp = System.IO.File.ReadAllLines(Info.path);
            Info.FirstLine = emp[0];
            for (int i = 1; i < emp.Length; i++)
            {
                string[] emps = emp[i].Split(';');
                string[] date = emps[3].Split('.');
                int.TryParse(date[2], out int day);
                int.TryParse(date[1], out int month);
                int.TryParse(date[0], out int year);
                int.TryParse(emps[5], out int Salary);
                int.TryParse(emps[6], out int SalaryCurrency);
                int.TryParse(emps[7], out int CompanyRole);
                DateTime BirthDate = new DateTime(day, month, year);

                Employee ee = new Employee(emps[0], emps[1], emps[2], BirthDate, emps[4], Salary, (Currency)SalaryCurrency, (Role)CompanyRole);
                ee.PropertyChanged += Employee_PropertyChanged;
                Info.Employees.Add(ee);
                Info.Change = false;
            }
        }
    }
}
