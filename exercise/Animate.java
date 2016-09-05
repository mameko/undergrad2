import javax.swing.*;
import java.awt.*;

public class Animate
{
	int x = 1;
	int y = 1;
	
	public static void main (String[] args)
	{
		Animate gui = new Animate();
		gui.go();
	}

	public void go()
	{
		JFrame frame = new JFrame();
		MyDrawP drawP = new MyDrawP();
		frame.setSize(500,300);
		frame.getContentPane().add(drawP);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);

		for(int i=0;i<124;i++,x++,y++)
		{
			x++;			
			drawP.repaint();
			try
			{
				Thread.sleep(50);
			}catch(Exception ex){}
		}
	}

	class MyDrawP extends JPanel
	{
		public void paintComponent(Graphics g)
		{
			g.setColor(Color.white);
			g.fillRect(0,0,500,300);
			g.setColor(Color.blue);
			g.fillRect(x,y,500-x*2,300-y*2);
		}
	}
}
		