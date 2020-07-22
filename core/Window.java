package core;

import units.Report;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


//CONSOLE-LOOKING VERSION --- NEEDS A LOT OF WORK ---
/*public class Window {
    private JTextArea textArea = new JTextArea();
    private JScrollPane scrollPane = new JScrollPane(textArea);
    private JFrame frame = new JFrame();
    private String input = "";



    public Window(inputHandler inputHandler) {
        frame.setLayout(null);
        frame.setVisible(true);
        frame.setSize(800,600);
        frame.add(scrollPane);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setFocusable(true);
        frame.requestFocus();
        frame.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e){
                switch (KeyEvent.getKeyText(e.getKeyCode())) {
                    case "Backspace":
                        if (input.length() > 0) {
                            input = input.substring(0, input.length()-1);
                            textArea.setText(textArea.getText().substring(0, textArea.getText().length()-1));
                        }
                        break;
                    case "Enter":
                        textArea.setText(textArea.getText().concat("\n"));
                        inputHandler.doSomething(input);
                        input = "";
                        break;
                    case "Space":
                        textArea.setText(textArea.getText().substring(0, textArea.getText().length()- input.length()));
                        input = input.concat(" ");
                        textArea.setText(textArea.getText().concat(input));
                        break;
                    default:
                        textArea.setText(textArea.getText().substring(0, textArea.getText().length()- input.length()));
                        input = input.concat(KeyEvent.getKeyText(e.getKeyCode()).toLowerCase());
                        textArea.setText(textArea.getText().concat(input));
                        //WIP lotsa problems
                }
            }
        });

        textArea.setEnabled(false);
        textArea.setDisabledTextColor(Color.white);
        textArea.setBackground(Color.black);
        textArea.setLineWrap(true);
        textArea.setWrapStyleWord(true);

        scrollPane.setBounds(0,0,frame.getWidth(), 560);
    }

    public void println(String str) {
        textArea.setText(textArea.getText().concat(str + "\n"));
    }
    public void println() {
        textArea.setText(textArea.getText().concat("\n"));
    }
    public void print(String str) {
        textArea.setText(textArea.getText().concat(str));
    }

    public void clearWindow() {
        textArea.setText("");
    }
}*/

//INPUT-BOX VERSION
public class Window {
    private JTextArea textArea;
    private JTextField textField;
    private Interpreter interpreter;
    private Report lastReport;
    private String savedScreen;


    public Window() {
        this.interpreter = new Interpreter();
        this.savedScreen = "";

        JFrame frame = new JFrame("Dinoszauruszon Lovagló Gépfegyveres Amazonok");
        frame.getContentPane().setPreferredSize(new Dimension(960, 540));
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        JPanel panel = new JPanel();
        panel.setBackground(Color.black);
        panel.setLayout(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();

        this.textArea = new JTextArea();
        JScrollPane scrollPane = new JScrollPane(textArea);
        scrollPane.setBorder(null);

        textArea.setBackground(Color.black);
        textArea.setDisabledTextColor(Color.white);
        textArea.setLineWrap(true);
        textArea.setWrapStyleWord(true);
        textArea.setEnabled(false);
        Font font = new Font("font", Font.PLAIN, 16);
        textArea.setFont(font);

        this.textField = new JTextField();
        textField.setBorder(null);
        textField.setBackground(Color.black);
        textField.setForeground(Color.white);
        textField.setFocusable(true);
        textField.requestFocus();
        textField.setFont(font);
        textField.addActionListener((ActionEvent actionEvent) -> {
            this.textArea.append(textField.getText() + "\n");
            this.lastReport = this.interpreter.interpret(this.textField.getText());
            this.textField.setText("");
            if (this.lastReport.getCode()) {
                String temp = this.savedScreen;
                this.savedScreen = this.textArea.getText().concat("\n---End of turn---\n\n");
                this.textArea.setText(temp);
            }
            textArea.append(this.lastReport.getPrint());
            textArea.setCaretPosition(textArea.getDocument().getLength());
        });

        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.weightx = 1;
        gbc.weighty = 100;
        gbc.fill = GridBagConstraints.BOTH;
        panel.add(scrollPane, gbc);
        gbc.gridy = 1;
        gbc.weighty = 1;
        panel.add(textField, gbc);

        frame.add(panel);
        frame.pack();
        frame.setVisible(true);
    }

    public void print(String str) {
        this.textArea.append(str);
    }
}