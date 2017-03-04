using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Project_MapEditorV1;
using System.IO;

namespace FrameWork.FrameWork.QuadTree
{
    class QuadTree
    {
        QuadTreeNode m_root;
        Rectangle m_rectangle;

        public QuadTree(Rectangle rectangle)
        {
            m_rectangle = rectangle;
            m_root = new QuadTreeNode(m_rectangle);

            m_root.strNodeIDToPlus = "1";
            m_root.strNodeID = m_root.strNodeIDToPlus.PadRight(8, '0');
            m_root.nodeID = Convert.ToInt32(m_root.strNodeID, 2);
        }

        public int Count { get { return m_root.Count; } }

        public void Insert(MyImage item)
        {
            Global.levelNode = 1;
            m_root.Insert(item);
        }

        public List<MyImage> Query(Rectangle area)
        {
            return m_root.Query(area);
        }

        public void SaveQT(TextWriter tw)
        {
            m_root.SaveQuadTree(tw);
        }
    }
}
