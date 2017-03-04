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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
using System.Diagnostics;
using FrameWork.FrameWork.QuadTree;

namespace Project_MapEditorV1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private int _Width;
        private int _Height;
        private int _XPos;
        private int _YPos;
        private int _Level;
        private int _Life;
        /*private string _NameMap;*/
        private MyImage[,] _MapTitle;
        WindownNew _dlgNew;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void _ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string path = _listBox1.SelectedIndex.ToString() + ".png";
            _ImageSelect.Source = BitmapFrame.Create(new Uri(path, UriKind.Relative));
        }

        private void EditorMap(object sender, MouseButtonEventArgs e)
        {
            MyImage fe1 = (MyImage)e.Source;
            fe1.Index = _listBox1.SelectedIndex;
        }
       
        private void New_Click(object sender, RoutedEventArgs e)
        {
            _dlgNew = new WindownNew();
            _dlgNew.ShowDialog();
            if (_dlgNew.IsOK != true)
            {
                return;
            }

            Mouse.OverrideCursor = Cursors.Wait;
            _LabelWidth.Content = _Width = _dlgNew.MapWidth;
            _LabelHeight.Content= _Height = _dlgNew.MapHeight;
            _NameMap.Content = _dlgNew.MapName;
            _labelXPos.Content = _XPos = _dlgNew.XPos;
            _LabelYPos.Content= _YPos = _dlgNew.YPos;
            _Level = _dlgNew.LEVEL;
            _Life = _dlgNew.TIMES; 
            
            _WrapPanelMain.Children.Clear();
            _WrapPanelMain.Width = 25 * (1 + _Width);
            _WrapPanelMain.Height = 25 * (1 + _Height);
            
            _MapTitle = new MyImage[_Width, _Height];

            for (int j = 0; j < _Height; j++)
            {
                TextBlock Num = new TextBlock();
                Num.Height = 25;
                Num.Width = 25;
                Num.Text = (_Height - 1 - j).ToString();
                Num.TextAlignment = TextAlignment.Center;
                _WrapPanelMain.Children.Add(Num);

                for (int i = 0; i < _Width; i++)
                {
                    _MapTitle[i, j] = new MyImage();
                    _MapTitle[i, j].Index = 0;
                    _MapTitle[i, j].MouseLeftButtonDown += EditorMap;
                    _MapTitle[i, j].Margin = new Thickness(0, 0, 0, 0);
                    _MapTitle[i, j].Height = 25;
                    _MapTitle[i, j].Width = 25;
                    _MapTitle[i, j].ToolTip = "[" + i.ToString() + "," + (_Height - 1 - j).ToString() + "]";
                    _WrapPanelMain.Children.Add(_MapTitle[i, j]);
                }
            }

            for (int i = 0; i < _Width + 1; i++)
            {
                TextBlock Num = new TextBlock();
                Num.Text = (i - 1).ToString();
                if (i == 0)
                {
                    Num.Text = " ";
                }
                Num.Height = 25;
                Num.Width = 25;
                Num.TextAlignment = TextAlignment.Center;
                _WrapPanelMain.Children.Add(Num);
            }

            Mouse.OverrideCursor = null;
        }

        private void Open_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.FileName = "Document"; // Default file name
            dlg.DefaultExt = ".txt"; // Default file extension
            dlg.Filter = "Text documents (.txt)|*.txt"; // Filter files by extension

            // Show open file dialog box
            Nullable<bool> result = dlg.ShowDialog();

            // Process open file dialog box results
            if (result == true)
            {
                // Open document
                string filename = dlg.FileName;               
                string[] s1 =dlg.SafeFileName.Split('.');
                _NameMap.Content = s1[0];

                TextReader tr = new StreamReader(filename);
                string s = tr.ReadLine();                
                string[] st = s.Split(' ');
                _labelXPos.Content = _XPos = Convert.ToInt32(st[0]);
                _LabelYPos.Content = _YPos = Convert.ToInt32(st[1]);
                _LabelWidth.Content =_Width = Convert.ToInt32(st[2]);
                _LabelHeight.Content = _Height = Convert.ToInt32(st[3]);
                _LabelLevel.Content = _Level = Convert.ToInt32(st[4]);
                _LabelTime.Content = _Life = Convert.ToInt32(st[5]);
                

                _WrapPanelMain.Children.Clear();
                _WrapPanelMain.Width = 25 * (1 + _Width);
                _WrapPanelMain.Height = 25 * (1 + _Height);
                _MapTitle = new MyImage[_Width, _Height];
            
                for (int j = 0; j < _Height; j++)
                {
                    TextBlock Num = new TextBlock();
                    Num.Height = 25;
                    Num.Width = 25;
                    Num.Text = (_Height - 1 - j).ToString();
                    Num.TextAlignment = TextAlignment.Center;
                    _WrapPanelMain.Children.Add(Num);

                    string sj = tr.ReadLine();
                    string[] sj1 = sj.Split(' ');

                    for (int i = 0; i < _Width; i++)
                    {
                        _MapTitle[i, j] = new MyImage();
                        _MapTitle[i, j].Index = Convert.ToInt32(sj1[i]) ;
                        _MapTitle[i, j].MouseLeftButtonDown += EditorMap;
                        _MapTitle[i, j].Margin = new Thickness(0, 0, 0, 0);
                        _MapTitle[i, j].Height = 25;
                        _MapTitle[i, j].Width = 25;
                        _MapTitle[i, j].ToolTip = "[" + i.ToString() + "," + (_Height - 1 - j).ToString() + "]";
                        _WrapPanelMain.Children.Add(_MapTitle[i, j]);
                    }
                }

                for (int i = 0; i < _Width + 1; i++)
                {
                    TextBlock Num = new TextBlock();
                    Num.Text = (i - 1).ToString();
                    if (i == 0)
                    {
                        Num.Text = " ";
                    }
                    Num.Height = 25;
                    Num.Width = 25;
                    Num.TextAlignment = TextAlignment.Center;
                    _WrapPanelMain.Children.Add(Num);
                }
                tr.Close();
            }
        }

        private void Save_Click(object sender, RoutedEventArgs e)
        {
            QuadTree myQT;

            bool iBoss = false; bool iPole = false; bool iBuilding = false;
            for (int j = 0; j < _Height; j++)
            {
                for (int i = 0; i < _Width; i++)
                {
                    if (_MapTitle[i, j].Index== 40)
                    {
                        iBoss = true;
                    }
                    if (_MapTitle[i, j].Index == 38)
                    {
                        iPole = true;
                    }
                    if (_MapTitle[i, j].Index == 22)
                    {
                        iBuilding = true;
                    }
                }              
            }

            if ((iPole == false) || (iBoss == false) || (iBuilding == false))
            {
                MessageBox.Show("Must pitch Boss, Pole and Building in to map");
                return;
            }

            // Configure save file dialog box
            Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
            dlg.FileName = _NameMap.Content.ToString(); // Default file name
            dlg.DefaultExt = ".text"; // Default file extension
            dlg.Filter = "Text documents (.txt)|*.txt"; // Filter files by extension

            // Show save file dialog box
            Nullable<bool> result = dlg.ShowDialog();

            // Process save file dialog box results
            if (result == true)
            {
                
                // Save document
                string filename = dlg.FileName;
                TextWriter tw = new StreamWriter(filename);
                tw.Write(_XPos.ToString() + " ");
                tw.Write(_YPos.ToString() + " ");
                tw.Write(_Width.ToString() + " ");
                tw.Write(_Height.ToString() + " ");
                tw.Write(_Level.ToString() + " ");
                tw.WriteLine(_Life.ToString());

                myQT = new QuadTree(new Rectangle(0, _Width * 50, _Height * 50, 0));

                for (int j = 0; j < _Height;j++)
                {
                    for (int i = 0; i < _Width; i++ )
                    {
                        if (_MapTitle[i, j].Index == 40)
                        {
                            _MapTitle[i, j].RECT = new Rectangle(i * 50, (i + 2) * 50, (_Height - j) * 50 + 60, (_Height - 1 - j) * 50);
                        }
                        else
                        if (_MapTitle[i, j].Index == 1)
                        {
                            _MapTitle[i, j].RECT = new Rectangle(i * 50, (i + 1) * 50, (_Height - j) * 50 + 22, (_Height - 1 - j) * 50);
                        }else
                        if (_MapTitle[i, j].Index == 22)
                        {
                            _MapTitle[i, j].RECT = new Rectangle(i * 50, (i + 1) * 50 + 450, (_Height - j) * 50 + 500, (_Height - 1 - j) * 50);
                        }
                        else
                        if (_MapTitle[i, j].Index == 38)
                        {
                            _MapTitle[i, j].RECT = new Rectangle(i * 50, (i + 1) * 50, (_Height - j) * 50, (_Height - 9 - j) * 50);
                        }
                        else
                        {
                            _MapTitle[i, j].RECT = new Rectangle(i * 50, (i + 1) * 50, (_Height - j) * 50, (_Height - 1 - j) * 50);
                        }
                        
                        if (_MapTitle[i,j].Index != 0)
                        {
                            myQT.Insert(_MapTitle[i, j]);
                        }

                        tw.Write(_MapTitle[i, j].Index.ToString("00") + " ");
                    }
                    tw.WriteLine();
                }

                myQT.SaveQT(tw);
                
                tw.Close();

            }
        }
        
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Manual_Click(object sender, RoutedEventArgs e)
        {
            Window dlg = new ManualWindow();
            dlg.ShowDialog();

        }

        private void Infor_Click(object sender, RoutedEventArgs e)
        {
            Window dlg = new InforWindown();
            dlg.ShowDialog();
        }

        private void Edit_Click(object sender, RoutedEventArgs e)
        {
            EditWindow dlg = new EditWindow();
            dlg._MapName.Text = dlg.MapName = _NameMap.Content.ToString();
            dlg.MapWidth = _Width;
            dlg.MapHeight = _Height;
            dlg.XPos = _XPos;
            dlg._XPos.Text = _XPos.ToString();
            dlg.YPos = _YPos;
            dlg._YPos.Text = _YPos.ToString();
            dlg.Level.Text = _Level.ToString();
            dlg.Times.Text = _Life.ToString();

            dlg.ShowDialog();
            if (dlg.IsOK == true)
            {
                _NameMap.Content = dlg.MapName;
               _labelXPos.Content = _XPos = dlg.XPos ;
               _LabelYPos.Content = _YPos = dlg.YPos;
               _Level = dlg.LEVEL;
               _Life = dlg.TIMES;
            }
        }
       
    }

    public class MyImage : Image
    {
        private int _Index;

        private Rectangle rect;

        public Rectangle RECT
        {
            get { return rect; }
            set { rect = value; }
        }

        public int Index
        {
            get { return _Index; }
            set 
            { 
                _Index = value;
                string path = _Index.ToString() + ".png";               
                this.Source = BitmapFrame.Create(new Uri(path, UriKind.Relative));              
            }
        }

        public MyImage() 
        {
            this.MouseRightButtonDown += DeleteEditorMap;
        }

        private void DeleteEditorMap(object sender, MouseButtonEventArgs e)
        {
            MyImage fe1 = (MyImage)e.Source;
            fe1.Index = 0;
        }
    }
}
