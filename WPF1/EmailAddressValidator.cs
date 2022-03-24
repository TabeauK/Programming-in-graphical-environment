using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Globalization;

namespace WPF_Lab1_Tue
{
    class EmailAddressValidator : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            if (value is string)
            {
                if (value==null || (value as string).Contains('@'))
                {
                    return new ValidationResult(true, "");
                }
            }
            return new ValidationResult(false, "Not an Email");
        }
    }

    class NumberValidator : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            int temp;
            if(int.TryParse(((string)value),out temp))
            {
                return new ValidationResult(true, "");
            }
            return new ValidationResult(false, "Not a Number");
        }
    }
}
