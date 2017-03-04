using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Project_MapEditorV1;
using System.IO;

namespace FrameWork.FrameWork.QuadTree
{
    class QuadTreeNode
    {
        public List<MyImage> m_contents = new List<MyImage>();
        Rectangle m_bounds;
        List<QuadTreeNode> m_nodes = new List<QuadTreeNode>(4);

        public string strNodeIDToPlus;
        public string strNodeID;
        public int nodeID;

        public List<MyImage> Contents
        {
            get
            {
                List<MyImage> Result = new List<MyImage>();
                Result.AddRange(m_contents);
                return Result;
            }
        }

        public QuadTreeNode(Rectangle bounds)
        {
            m_bounds = bounds;
        }

        public Rectangle Bounds
        {
            get { return m_bounds; }
        }

        public int Count
        {
            get
            {
                int count = 0;
                foreach (QuadTreeNode node in m_nodes)
                    count += node.Count;

                count += this.m_contents.Count;
                return count;
            }
        }

        public bool IsEmpty
        {
            get { return m_bounds.IsEmpty || m_nodes.Count == 0; }
        }

        public List<MyImage> SubTreeContents
        {
            get
            {
                List<MyImage> results = new List<MyImage>();

                foreach (QuadTreeNode node in m_nodes)
                    results.AddRange(node.SubTreeContents);

                results.AddRange(this.m_contents);
                return results;
            }
        }

        private void CreateSubNodes()
        {
            // the maximum level node 
            if (Global.levelNode > 5)
                return;

            int halfWidth = (m_bounds.Width / 2);
            int halfHeight = (m_bounds.Height / 2);

            m_nodes.Add(new QuadTreeNode(new Rectangle(m_bounds.Left, m_bounds.Left + halfWidth, m_bounds.Top, m_bounds.Top - halfHeight)));
            m_nodes.ElementAt<QuadTreeNode>(0).strNodeIDToPlus = this.strNodeIDToPlus + "00";
            m_nodes.ElementAt<QuadTreeNode>(0).strNodeID = m_nodes.ElementAt<QuadTreeNode>(0).strNodeIDToPlus.PadRight(7, '0');
            m_nodes.ElementAt<QuadTreeNode>(0).nodeID = Convert.ToInt32(strNodeIDToPlus, 2);

            m_nodes.Add(new QuadTreeNode(new Rectangle(m_bounds.Left, m_bounds.Left + halfWidth, m_bounds.Top - halfHeight, m_bounds.Bottom)));
            m_nodes.ElementAt<QuadTreeNode>(1).strNodeIDToPlus = this.strNodeIDToPlus + "01";
            m_nodes.ElementAt<QuadTreeNode>(1).strNodeID = m_nodes.ElementAt<QuadTreeNode>(1).strNodeIDToPlus.PadRight(7, '0');
            m_nodes.ElementAt<QuadTreeNode>(1).nodeID = Convert.ToInt32(strNodeIDToPlus, 2);
                
            m_nodes.Add(new QuadTreeNode(new Rectangle(m_bounds.Left + halfWidth, m_bounds.Right, m_bounds.Top - halfHeight, m_bounds.Bottom)));
            m_nodes.ElementAt<QuadTreeNode>(2).strNodeIDToPlus = this.strNodeIDToPlus + "10";
            m_nodes.ElementAt<QuadTreeNode>(2).strNodeID = m_nodes.ElementAt<QuadTreeNode>(2).strNodeIDToPlus.PadRight(7, '0');
            m_nodes.ElementAt<QuadTreeNode>(2).nodeID = Convert.ToInt32(strNodeIDToPlus, 2);
                
            m_nodes.Add(new QuadTreeNode(new Rectangle(m_bounds.Left + halfWidth, m_bounds.Right, m_bounds.Top, m_bounds.Top - halfHeight)));
            m_nodes.ElementAt<QuadTreeNode>(3).strNodeIDToPlus = this.strNodeIDToPlus + "11";
            m_nodes.ElementAt<QuadTreeNode>(3).strNodeID = m_nodes.ElementAt<QuadTreeNode>(3).strNodeIDToPlus.PadRight(7, '0');
            m_nodes.ElementAt<QuadTreeNode>(3).nodeID = Convert.ToInt32(strNodeIDToPlus, 2);
        }

        public void Insert(MyImage item)
        {
            if (!m_bounds.Contains(item.RECT))
            {
                return;
            }

            if (m_nodes.Count == 0)
            {
                CreateSubNodes();
            }

            QuadTreeNode destTree = getDestTreeNode(item);
            if (destTree == this)
            {
                this.m_contents.Add(item);
            }
            else
            {
                Global.levelNode++;
                destTree.Insert(item);
            }
        }

        private QuadTreeNode getDestTreeNode(MyImage item)
        {
            QuadTreeNode destTree = this;
            foreach (QuadTreeNode node in m_nodes)
            {
                if (node.Bounds.Contains(item.RECT))
                {
                    destTree = node;
                    break;
                }
            }
            return destTree;
        }

        public List<MyImage> Query(Rectangle queryArea)
        {
            // create a list of the items that are found
            List<MyImage> results = new List<MyImage>();

            // this quad contains items that are not entirely contained by
            // it's four sub-quads. Iterate through the items in this quad 
            // to see if they intersect.
            /*foreach (MyObject item in this.Contents)
            {
                if (queryArea.IntersectsWith(item.Rectangle))
                    results.Add(item);
            }*/
            for (int i = 0; i < m_contents.Count; )
            {
                if (queryArea.Intersects(m_contents[i].RECT))
                {
                    results.Add(m_contents[i]);
                    m_contents.Remove(m_contents[i]);
                }
                else i++;
            }

            foreach (QuadTreeNode node in m_nodes)
            {
                if (node.IsEmpty)
                    continue;

                if (node.Bounds.Contains(queryArea))
                {
                    results.AddRange(node.Query(queryArea));
                    break;
                }

                if (queryArea.Contains(node.Bounds))
                {
                    results.AddRange(node.SubTreeContents);
                    continue;
                }

                if (node.Bounds.Intersects(queryArea))
                {
                    results.AddRange(node.Query(queryArea));
                }
            }
            return results;
        }

        public void SaveQuadTree(TextWriter tw)
        {
            if (IsEmpty)
            {
                return;
            }

            foreach (QuadTreeNode node in m_nodes)
            {
                node.SaveQuadTree(tw);
            }

            if (this.m_contents.Count != 0)
            {
                tw.Write(strNodeIDToPlus + " ");
                //tw.Write(m_bounds.Left.ToString("00000") + " " + m_bounds.Right.ToString("00000") + " " +
                //    m_bounds.Top.ToString("00000") + " " + m_bounds.Bottom.ToString("00000") + " ");
                //tw.Write(this.m_contents.Count.ToString("00") + " ");

                for (int i = 0; i < this.m_contents.Count; i++)
                {
                    tw.Write(this.m_contents[i].Index.ToString("00") + " ");
                    tw.Write(this.m_contents[i].RECT.Left.ToString("00000") + " " + this.m_contents[i].RECT.Top.ToString("00000") + " ");
                    //tw.Write(this.m_contents[i].RECT.Left.ToString("00000") + " " + this.m_contents[i].RECT.Right.ToString("00000") + " " +
                    //this.m_contents[i].RECT.Top.ToString("00000") + " " + this.m_contents[i].RECT.Bottom.ToString("00000") + " ");
                }

                tw.WriteLine();
            }
        }
    }
}
