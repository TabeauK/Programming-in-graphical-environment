using System.Windows;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using Microsoft.Win32;

namespace WPF_Lab1_Tue
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public struct Image
        {
            public string Path { get; set; }
        }

        public struct MainWindowData
        {
            public List<string> Hours { get; set; }
            public List<string> Departaments { get; set; }
            public ObservableCollection<Image> Images { get; set; }
        }

        public MainWindowData MainWindowDataData
        {
            get { return (MainWindowData)GetValue(MainWindowDataDataProperty); }
            set { SetValue(MainWindowDataDataProperty, value); }
        }

        public string DescriptionText { get; set; }
        public string EmailAddress { get; set; }
        public int PhoneNumber { get; set; }

        public static readonly DependencyProperty MainWindowDataDataProperty =
            DependencyProperty.Register("MainWindowDataData", typeof(MainWindowData), typeof(MainWindow), new PropertyMetadata(null));

        public MainWindow()
        {

            InitializeComponent();

            List<string> departaments = new List<string>()
            {
                "--Select A Value--", "IT Group", "HR Group",
                "Marketing Group", "Development Group", "Curstomer Service Group"
            };

            List<string> hours = new List<string>()
            {
                "01:00", "02:00", "03:00", "04:00", "05:00", "06:00", "07:00", "08:00", "09:00", "10:00", "11:00", "12:00",
                "13:00", "14:00", "15:00", "16:00", "17:00", "18:00", "19:00", "20:00", "21:00", "22:00", "23:00", "00:00"
            };



            ObservableCollection<Image> images = new ObservableCollection<Image>()
            {
                new Image() { Path = $"http://ajaxuploader.com/images/drag-drop-file-upload.png" },
                new Image() { Path = $"http://ajaxuploader.com/images/drag-drop-file-upload.png" },
            };

            MainWindowDataData = new MainWindowData() { Images = images, Departaments = departaments, Hours = hours };

        }

        

        private void TabControl_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {

        }

        private void Button_MouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "Jpg Files| *.jpg";
            if(ofd.ShowDialog()==true)
            {
                MainWindowDataData.Images.Add(new Image() { Path = ofd.FileName });
            }
        }
    }
}
