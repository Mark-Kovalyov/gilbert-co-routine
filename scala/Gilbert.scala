import java.awt.geom.{GeneralPath, Path2D}
import java.awt.{Dimension, Graphics, Graphics2D}
import javax.swing.JFrame;

object Guilbert extends App {
  val p = 5
  val u = 10

  def a(i: Int): Stream[(Int, Int)] =
    if (i > 0)
      d(i - 1) #::: (u, 0) #:: a(i - 1) #::: (0, u) #:: a(i - 1) #::: (-u, 0) #:: c(i - 1)
    else Stream.empty

  def b(i: Int): Stream[(Int, Int)] =
    if (i > 0)
      c(i - 1) #::: (-u, 0) #:: b(i - 1) #::: (0, -u) #:: b(i - 1) #::: (u, 0) #:: d(i - 1)
    else Stream.empty

  def c(i: Int): Stream[(Int, Int)] =
    if (i > 0)
      b(i - 1) #::: (0, -u) #:: c(i - 1) #::: (-u, 0) #:: c(i - 1) #::: (0, u) #:: a(i - 1)
    else Stream.empty

  def d(i: Int): Stream[(Int, Int)] =
    if (i > 0)
      a(i - 1) #::: (0, u) #:: d(i - 1) #::: (u, 0) #:: d(i - 1) #::: (0, -u) #:: b(i - 1)
    else Stream.empty

  val f = new JFrame() {
    override def paint(g: Graphics): Unit = {
      val g2 = g.asInstanceOf[Graphics2D];
      val polyline = new GeneralPath(Path2D.WIND_EVEN_ODD, 5000);
      polyline.moveTo(100, 100)
      a(p).scanLeft((100, 100))((a, b) => (a._1 + b._1, a._2 + b._2)).take(5000).foreach(
        point => polyline.lineTo(point._1, point._2)
      )
      g2.draw(polyline)
    }
  }

  f.setSize(new Dimension(500, 500))
  f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE)
  f.setVisible(true)
}
