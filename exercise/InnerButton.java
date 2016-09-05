import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
	
public class InnerButton
{
	JFrame frame;
	JButton b;

	public static void main(String[] args)
	{
		InnerButton gui = new InnerButton();
		gui.go();
	}
	
	public void go()
	{
		frame = new JFrame();
		b = new JButton("A");

		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(100,100);
		frame.setVisible(true);
		frame.getContentPane().add(b);
	
		b.addActionListener(new BListener());
	}

	class BListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			if(b.getText().equals("A"))
			{
				b.setText("B");
			}
			else 
				b.setText("A");
		}
	}
}	