using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;

namespace Lab2
{
    public class SalaryValidation : ValidationRule
    {
        private int minSalary;

        public int Min
        {
            get{ return minSalary; }
            set{ minSalary = value; }
        }

        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            if (!int.TryParse(value as string, out int val))
            {
                return new ValidationResult(true, "Please enter a number");
            }
            if (val < Min)
            {
                return new ValidationResult(false, $"Number is below the minimum salary ({minSalary})");
            }
            return new ValidationResult(true, null);
        }


    }

    public class ErrorMessage : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if(((ReadOnlyObservableCollection<ValidationError>)value).Count!=0)
            {
                return System.Windows.Visibility.Visible;
            }
            return System.Windows.Visibility.Collapsed;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }


    public class CeoDataTemplateSelector : DataTemplateSelector
    {
         public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            FrameworkElement elem = container as FrameworkElement;


            if (!(elem is null) && !(item is null) && item is MainWindow.Employee)
            {
                MainWindow.Employee emp = item as MainWindow.Employee;

                if(emp.CompanyRole == MainWindow.Role.CEO)
                {
                    return elem.FindResource("Ceo") as DataTemplate;
                }
                return elem.FindResource("NotCeo") as DataTemplate;
            }
            return null;
        }
    }

    public class STDCheck : IValueConverter
    {

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if((value as string)==(parameter as string))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if((bool)value)
            {
                return parameter as string;
            }
            else
            {
                return null;
            }
        }
    }



}
