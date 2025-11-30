import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * Write a description of class Login here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */

public class Login {
    String Username = "james3302";
    String Password = "pass";
    String msg = " ";
    JTextField txtUsername;
    JTextField txtPassword;

    public static void main(String[] args) {
        Login gui = new Login();
        gui.go();
    }

    public void go() {  
        JFrame frame = new JFrame();  
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  
        JPanel panel = new JPanel();  
        JLabel lblUsername = new JLabel("Username:");    
        JLabel lblPassword = new JLabel("Password:");  
        txtUsername = new JTextField(20);  
        txtPassword = new JTextField(20);  
        JButton btnLogin = new JButton("Login");  
        btnLogin.addActionListener(new LoginListener());  
        JButton btnCancel = new JButton("Cancel");  
        btnCancel.addActionListener(new CancelListener());  
        panel.add(lblUsername);  
        panel.add(txtUsername);  
        panel.add(lblPassword);  
        panel.add(txtPassword);      
        panel.add(btnLogin);  
        panel.add(btnCancel); 
        frame.getContentPane().add(BorderLayout.CENTER,panel);  
        frame.setSize(300,150);  
        frame.setVisible(true);  
    }  

    public class LoginListener implements ActionListener {  
        public void actionPerformed(ActionEvent event) {  
            if (Username.equals(txtUsername.getText())) {  
                if (Password.equals(txtPassword.getText())) msg = "Login Granted!";  
                else msg = "Login Denied";  
            } else { 
                msg = "Login Denied";  
            }
            JOptionPane.showMessageDialog(null,msg);            
        }  
    }

    public class CancelListener implements ActionListener{  
        public void actionPerformed(ActionEvent event){  
            txtUsername.setText(" ");  
            txtPassword.setText("");  
            txtUsername.requestFocus();  
        }  
    }  
}  