import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class CalcGUI extends JFrame
{
	private JTextField output;
	public CalcGUI()
	{
		super("Calculator");

		JMenuBar menu = new JMenuBar();
		JMenu file = new JMenu("File");
		JMenu about = new JMenu("About");
		menu.add(file);
		menu.add(about);
		setSize(270,230);

		JPanel out_p = new JPanel();
		output = new JTextField("",23);
		output.setEnabled(false);
		out_p.add(output);
		
		JPanel dumb_p = new JPanel();
		dumb_p.setLayout(new BorderLayout());
		
		add(dumb_p);
		dumb_p.add(new JButton("BS"), BorderLayout.EAST);
		
		JPanel wrap_p = new JPanel();
		wrap_p.setLayout(new BorderLayout());
		wrap_p.add(menu, BorderLayout.NORTH);
		wrap_p.add(out_p);
		wrap_p.add(dumb_p, BorderLayout.SOUTH);
		add(wrap_p, BorderLayout.NORTH);
		
		JPanel button_p = new JPanel();
		button_p.setLayout(new GridLayout(5,4));
		add(button_p, BorderLayout.SOUTH);
		
		JButton[] buttons = new JButton[9];
		
		for (int i = 0 ; i < 9 ; i++)
		{
			buttons[i]= new JButton(""+(i+1));
		}
		
		button_p.add(new JButton("Pi"));
		button_p.add(new JButton("x^y"));
		button_p.add(new JButton("sqrt"));
		button_p.add(new JButton("+"));
		button_p.add(buttons[6]);
		button_p.add(buttons[7]);
		button_p.add(buttons[8]);
		button_p.add(new JButton("-"));
		button_p.add(buttons[3]);
		button_p.add(buttons[4]);
		button_p.add(buttons[5]);
		button_p.add(new JButton("*"));
		button_p.add(buttons[0]);
		button_p.add(buttons[1]);
		button_p.add(buttons[2]);
		button_p.add(new JButton("/"));
		button_p.add(new JButton("C"));
		button_p.add(new JButton("0"));
		button_p.add(new JButton("."));
		button_p.add(new JButton("="));

		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}
	
	public static void main(String[] args)
	{
		JFrame f = new CalcGUI();
		f.setVisible(true);
	}
}
