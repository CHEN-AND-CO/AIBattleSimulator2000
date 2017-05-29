import java.awt.*;
//import java.awt.event.*;
import javax.swing.*;

public class AIBattleSimulator2000Client {

	 private static void createAndShowGUI() {
        //Create and set up the window.
        JFrame window = new JFrame("AIBattleSimulator2000Client");
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JLabel emptyLabel = new JLabel("");
        emptyLabel.setPreferredSize(new Dimension(800, 600));
        window.getContentPane().add(emptyLabel, BorderLayout.CENTER);

        window.pack();
        window.setVisible(true);
                    JPanel pan = new JPanel();
    //Définition de sa couleur de fond
    pan.setBackground(Color.ORANGE);        
    //On prévient notre JFrame que notre JPanel sera son content pane
    window.setContentPane(pan);               
    window.setVisible(true);
    }

    public static void main(String[] args) {
    	javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();
            }
        });
    }

}