import java.awt.Graphics;
import java.awt.Graphics2D;
import javax.swing.JPanel;

/**
 * Write a description of class Renderer here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */

public class Renderer extends JPanel {

	private static final long serialVersionUID = 1L;

	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);

		Pong.pong.render((Graphics2D) g);
	}
}
