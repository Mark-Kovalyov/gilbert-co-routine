struct Point
    {
        Int32 x_;
        Int32 y_;

        public Point(Int32 x, Int32 y)
        {
            x_ = x;
            y_ = y;
        }

        public void print() {
            Console.WriteLine($"{x_}, {y_}");
        }
    }

    class Gilbert2
    {
        const int u = 1;  // pixel step

        int glx;
        int gly;

        // BGI emulation
        Point linerel(int x, int y)
        {
            glx += x;
            gly += y;
            return new Point(glx, gly);
        }

        Point moveto(int x, int y)
        {
            glx = x;
            gly = y;
            return new Point(glx, gly);
        }


        // Elements of curve
        IEnumerable<Point> a(int i)
        {
            if (i > 0)
            {
                foreach(var p in d(i - 1)) yield return p;
                yield return linerel(+u, 0);
                foreach (var p in a(i - 1)) yield return p;
                yield return linerel(0, u);
                foreach (var p in a(i - 1)) yield return p;
                yield return linerel(-u, 0);
                foreach (var p in c(i - 1)) yield return p;
            }
        }

        IEnumerable<Point> b(int i)
        {
            if (i > 0)
            {
                foreach (var p in c(i - 1)) yield return p;
                yield return linerel(-u, 0);
                foreach (var p in b(i - 1)) yield return p;
                yield return linerel(0, -u);
                foreach (var p in b(i - 1)) yield return p;
                yield return linerel(u, 0);
                foreach (var p in d(i - 1)) yield return p;
            }
        }

        IEnumerable<Point> c(int i)
        {
            if (i > 0)
            {
                foreach (var p in b(i - 1)) yield return p;
                yield return linerel(0, -u);
                foreach (var p in c(i - 1)) yield return p;
                yield return linerel(-u, 0);
                foreach (var p in c(i - 1)) yield return p;
                yield return linerel(0, u);
                foreach (var p in a(i - 1)) yield return p;
            }
        }

        IEnumerable<Point> d(int i)
        {
            if (i > 0)
            {
                foreach (var p in a(i - 1)) yield return p;
                yield return linerel(0, u);
                foreach (var p in d(i - 1)) yield return p;
                yield return linerel(u, 0);
                foreach (var p in d(i - 1)) yield return p;
                yield return linerel(0, -u);
                foreach (var p in b(i - 1)) yield return p;
            }
        }

        public IEnumerable<Point> GetPoints(int level)
        {
            yield return moveto(0, 0);
            foreach (var p in a(level)) yield return p;
        }

    }

    class Program
    {
        static void Main(string[] args) {
            var g = new Gilbert2();
            foreach (var p in g.GetPoints(2)) p.print();
        }
    }