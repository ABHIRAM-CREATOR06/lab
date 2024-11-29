import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TrafficLightSystem extends JFrame implements ActionListener {
    private JPanel lightPanel;
    private JButton redButton, yellowButton, greenButton;
    private Color currentColor = Color.GRAY;

    public TrafficLightSystem() {
        // Create the frame
        setTitle("Traffic Light System");
        setSize(300, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Create the panel for the lights
        lightPanel = new JPanel() {
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);
                g.setColor(currentColor);
                g.fillOval(100, 100, 100, 100);
            }
        };

        // Create the buttons
        redButton = new JButton("Red");
        yellowButton = new JButton("Yellow");
        greenButton = new JButton("Green");

        // Add action listeners
        redButton.addActionListener(this);
        yellowButton.addActionListener(this);
        greenButton.addActionListener(this);

        // Add the panel and buttons to the frame
        add(lightPanel, BorderLayout.CENTER);
        JPanel buttonPanel = new JPanel();
        buttonPanel.add(redButton);
        buttonPanel.add(yellowButton);
        buttonPanel.add(greenButton);
        add(buttonPanel, BorderLayout.SOUTH);

        setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == redButton) {
            currentColor = Color.RED;
        } else if (e.getSource() == yellowButton) {
            currentColor = Color.YELLOW;
        } else if (e.getSource() == greenButton) {
            currentColor = Color.GREEN;
        }
        lightPanel.repaint();
    }

    public static void main(String[] args) {
        new TrafficLightSystem();
    }
}



