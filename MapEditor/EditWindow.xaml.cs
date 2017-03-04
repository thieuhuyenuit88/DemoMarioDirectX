using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Project_MapEditorV1
{
    /// <summary>
    /// Interaction logic for EditWindow.xaml
    /// </summary>
    public partial class EditWindow : Window
    {
        public bool IsOK
        {
            get;
            set;
        }
        public int MapWidth
        {
            get;
            set;
        }
        public int MapHeight
        {
            get;
            set;
        }
        public int XPos
        {
            get;
            set;
        }
        public int YPos
        {
            get;
            set;
        }
        public string MapName
        {
            get;
            set;
        }
        public int LEVEL
        {
            get;
            set;
        }
        public int TIMES
        {
            get;
            set;
        }
        public EditWindow()
        {
            InitializeComponent();
        }

        private void OK_Click(object sender, RoutedEventArgs e)
        {
            try
            { XPos = Convert.ToInt32(_XPos.Text); }
            catch (FormatException)
            {
                MessageBox.Show("Value Position X ='" + _XPos.Text + "'is not in a recognizable format.", "Error");
                return;
            }
            try
            { YPos = Convert.ToInt32(_YPos.Text); }
            catch (FormatException)
            {
                MessageBox.Show("Value Position Y ='" + _YPos.Text + "'is not in a recognizable format.", "Error");
                return;
            }
            if (XPos < 0 || XPos >= MapWidth)
            {
                MessageBox.Show("A value Start position X must: 0<= x < " + MapWidth.ToString());
                return;
            }
            if (YPos < 0 || YPos >= MapWidth)
            {
                MessageBox.Show("A value Start position Y must: 0<= y < "+ MapHeight.ToString());
                return;
            }
            try
            { 
                LEVEL = Convert.ToInt32(Level.Text);
            }
            catch (FormatException)
            {
                MessageBox.Show("Value level: "+Level.Text+"is not in a recognizable format.", "Error");
                return;
            }
            try
            {
                TIMES = Convert.ToInt32(Times.Text);
            }
            catch (FormatException)
            {
                MessageBox.Show("Value level: " + Times.Text + "is not in a recognizable format.", "Error");
                return;
            }
            TIMES = Convert.ToInt32(Times.Text);
            MapName = _MapName.Text;
            IsOK = true;
            this.Close();
        }
        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            IsOK = false;
            this.Close();
        }

        private void _MapName_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

    }
}
