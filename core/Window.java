package core;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.border.Border;

public class Window {
  private JTextArea textArea = new JTextArea();
  
  private JTextField textField = new JTextField();
  
  private inputHandler inputHandler = new inputHandler();
  
  private String player1Content = "";
  
  private String player2Content = "";
  
  public Window() {
    JFrame frame = new JFrame("Dinoszauruszon Lovagló Gépfegyveres Amazonok");
    frame.getContentPane().setPreferredSize(new Dimension(960, 540));
    frame.setDefaultCloseOperation(3);
    JPanel panel = new JPanel();
    panel.setBackground(Color.black);
    panel.setLayout(new GridBagLayout());
    GridBagConstraints gbc = new GridBagConstraints();
    JScrollPane scrollPane = new JScrollPane(this.textArea);
    scrollPane.setBorder((Border)null);
    this.textArea.setBackground(Color.black);
    this.textArea.setDisabledTextColor(Color.white);
    this.textArea.setLineWrap(true);
    this.textArea.setWrapStyleWord(true);
    this.textArea.setEnabled(false);
    Font font = new Font("font", 0, 16);
    this.textArea.setFont(font);
    this.textField.setBorder((Border)null);
    this.textField.setBackground(Color.black);
    this.textField.setForeground(Color.white);
    this.textField.setFocusable(true);
    this.textField.requestFocus();
    this.textField.setFont(font);
    this.textField.addActionListener(actionEvent -> {
          println(this.textField.getText());
          this.textArea.append(this.inputHandler.handle(this));
          this.textField.setText("");
        });
    gbc.gridx = 0;
    gbc.gridy = 0;
    gbc.weightx = 1.0D;
    gbc.weighty = 100.0D;
    gbc.fill = 1;
    panel.add(scrollPane, gbc);
    gbc.gridy = 1;
    gbc.weighty = 1.0D;
    panel.add(this.textField, gbc);
    frame.add(panel);
    frame.pack();
    frame.setVisible(true);
  }
  
  public String getInput() {
    return this.textField.getText();
  }
  
  public void println(String str) {
    this.textArea.append(str + "\n");
    this.textArea.setCaretPosition(this.textArea.getDocument().getLength());
  }
  
  public void print(String str) {
    this.textArea.append(str);
    this.textArea.setCaretPosition(this.textArea.getDocument().getLength());
  }
  
  public void changeWindow(boolean b) {
    if (b) {
      this.player1Content = this.textArea.getText();
      this.textArea.setText(this.player2Content);
      return;
    } 
    this.player2Content = this.textArea.getText();
    this.textArea.setText("");
    this.textArea.setText(this.player1Content);
  }
}
