import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SimpleCalculator {
    private JFrame frame;
    private JTextField display;
    private int temp, temp1, result;
    private String operator;

    public SimpleCalculator() {
        // Create the frame
        frame = new JFrame("Simple Calculator");
        display = new JTextField();
        JPanel panel = new JPanel();

        // Set up the frame
        frame.setSize(400, 500);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout());

        // Set up the display field
        display.setEditable(false);
        display.setHorizontalAlignment(JTextField.RIGHT);
        frame.add(display, BorderLayout.NORTH);

        // Set up the panel with buttons
        panel.setLayout(new GridLayout(4, 4));
        String[] buttons = {
            "7", "8", "9", "/",
            "4", "5", "6", "*",
            "1", "2", "3", "-",
            "0", "C", "=", "+"
        };

        for (String text : buttons) {
            JButton button = new JButton(text);
            button.addActionListener(new CalculatorAction());
            panel.add(button);
        }

        frame.add(panel, BorderLayout.CENTER);
        frame.setVisible(true);
    }

    private class CalculatorAction implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            String command = e.getActionCommand();

            if (command.equals("C")) {
                display.setText("");
            } else if (command.equals("=")) {
                temp1 = Integer.parseInt(display.getText());
                switch (operator) {
                    case "+":
                        result = temp + temp1;
                        break;
                    case "-":
                        result = temp - temp1;
                        break;
                    case "*":
                        result = temp * temp1;
                        break;
                    case "/":
                        if (temp1 != 0) {
                            result = temp / temp1;
                        } else {
                            display.setText("Error");
                            return;
                        }
                        break;
                }
                display.setText("" + result);
            } else if ("/*-+".contains(command)) {
                temp = Integer.parseInt(display.getText());
                operator = command;
                display.setText("");
            } else {
                display.setText(display.getText() + command);
            }
        }
    }

    public static void main(String[] args) {
        new SimpleCalculator();
    }
}
