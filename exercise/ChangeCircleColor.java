//bug 
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

class ChangeCircleColor extends JFrame implements ActionListener
{
	public static void main(String[] args)
	{
		ChangeCircleColor change = new ChangeCircleColor();
		JFrame MyFrame = new JFrame();
		JButton MyButton = new JButton("Change colors");
		Panel MyDrawPanel = new Panel();
		
		MyFrame.getContentPane.add(BorderLayout.SOUTH,MyButton);
		MyFrame.getContentPane.add(BorderLayout.CENTER,MyDrawPanel);
		
		MyFrame.setSize(500,500);
		MyFrame.setVisible(ture);
	
		MyFrame.setDefaultOperation(JFrame.EXIT_ON_CLOSE);

		MyButton.addActionListener(this);
	
	}

	public void paintComponent(Graphics g)
	{
		int red = (int)(Math.random()*255);
		int green = (int)(Math.random()*255);
		int blue = (int)(Math.random()*255);

		Color randomColor = new Color(red,green,blue);
		g.setColor(randomColor);
		g.FillOval(100,100,100,100);
		
	}

	public void actionPerformed(ActionEvent e)
	{
		g.repaint();
	}
	
}