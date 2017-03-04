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
    /// Interaction logic for WindownNew.xaml
    /// </summary>
    public partial class WindownNew : Window
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
        public WindownNew()
        {
            InitializeComponent();
            IsOK = false;
        }

        private void OK_Click(object sender, RoutedEventArgs e)
        {
            try
            { MapWidth = Convert.ToInt32(_MapWidth.Text); }            
            catch (FormatException)
            {   MessageBox.Show("Value Width ='" + _MapWidth.Text + "'is not in a recognizable format.", "Error");
                return; }
            try
            {MapHeight = Convert.ToInt32(_MapHeight.Text);}            
            catch (FormatException)
            {  MessageBox.Show("Value Height ='" + _MapHeight.Text + "'is not in a recognizable format.", "Error");
                return;}
            try
            { XPos = Convert.ToInt32(_XPos.Text); }
            catch (FormatException)
            {   MessageBox.Show("Value Position X ='" + _XPos.Text + "'is not in a recognizable format.", "Error");
                return;}
            try
            { YPos = Convert.ToInt32(_YPos.Text ); }
            catch (FormatException)
            {   MessageBox.Show("Value Position Y ='" + _YPos.Text + "'is not in a recognizable format.", "Error");
                return;  }
            if (XPos<0 || XPos>=MapWidth*50)
            {
                MessageBox.Show("A value Start position X must: 0<= x < " + MapWidth*50);
                return;
            }
            if (YPos < 0 || YPos >= MapHeight*50)
            {
                MessageBox.Show("A value Start position Y must: 0<= y < " + MapHeight*50);
                return;
            }
            LEVEL = Convert.ToInt32(level.Text);
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
    }
}
