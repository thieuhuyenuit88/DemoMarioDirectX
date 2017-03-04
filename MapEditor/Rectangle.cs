using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Project_MapEditorV1
{
    public class Rectangle
    {
        public int Left, Right;
        public int Width, Height;

        public int Top, Bottom;

        public Rectangle()
        {
            Left = Right = Top = Bottom = Width = Height = 0;
        }

        public Rectangle(int _left, int _right, int _top, int _bottom){
            Left = _left;
            Right = _right;
            Width = _right - _left;
            Height = _top - _bottom;
            Top = _top;
            Bottom = _bottom;
        }

        public bool Intersects(Rectangle rect)
        {
            int dh = (Math.Abs(Top - rect.Bottom) > Math.Abs(Bottom - rect.Top)) ? Math.Abs(Top - rect.Bottom) : Math.Abs(Bottom - rect.Top);
            int dw = (Math.Abs(Left - rect.Right) > Math.Abs(Right - rect.Left)) ? Math.Abs(Left - rect.Right) : Math.Abs(Right - rect.Left);

            return ((dw < ((Right - Left) + (rect.Right - rect.Left))) &&
                (dh < ((Top - Bottom) + (rect.Top - rect.Bottom))));
        }

        public bool Contains(Rectangle rect)
        {
            return (rect.Left >= Left)
                && (rect.Right <= Right)
                && (rect.Top <= Top)
                && (rect.Bottom >= Bottom);
        }

        public bool IsEmpty
        {
            get
            {
                return (Left == 0 && Right == 0 && Top == 0 && Bottom == 0
                    && Width == 0 && Height == 0);
            }
        }
    }
}
