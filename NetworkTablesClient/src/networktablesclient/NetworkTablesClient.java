package networktablesclient;

import java.io.*;
import edu.wpi.first.wpilibj.networktables.*;
import java.awt.FlowLayout;
import javax.swing.*;

public class NetworkTablesClient extends JFrame {

    int LeftFrontMotor;
    int LeftBackMotor;
    int RightFrontMotor;
    int RightBackMotor;
    int IntakeMotor;
    int FeederMotor;
    int ShooterMotor;
    int ClimberMotor;

    int LeftAnalog;
    int RightAnalog;
    int HalfSpeedToggle;
    int IntakeInButton;
    int IntakeOutButton;
    int FeederButton;
    int ShooterToggle;
    int ShooterIncreaseSpeed;
    int ShooterDecreaseSpeed;
    int ClimberButton;

    NetworkTable table;

    JFrame frame = new JFrame("ConfigTable 1622");
    static JTextArea text = new JTextArea(25, 40);
    static JScrollPane output = new JScrollPane(text, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
    final static JScrollBar vscroll = output.getVerticalScrollBar();

    public static void main(String[] args) {
        new NetworkTablesClient().run();
    }

    public NetworkTablesClient() {
        frame.setLayout(new FlowLayout());
        frame.setSize(500, 500);
        frame.setResizable(false);
        output.createVerticalScrollBar();
        output.setAutoscrolls(true);
        frame.add(output);
        text.setEditable(false);
        /*text.append('\n' + "Left Front Motor Port: " + table.getNumber("LeftFrontMotor", -1));
         text.append('\n' + "Left Back Motor Port: " + table.getNumber("LeftBackMotor", -1));
         text.append('\n' + "Right Front Motor Port: " + table.getNumber("RightFrontMotor", -1));
         text.append('\n' + "Right Back Motor Port: " + table.getNumber("RightBackMotor", -1));
         text.append('\n' + "Intake Motor Port: " + table.getNumber("IntakeMotor", -1));
         text.append('\n' + "Feeder Motor Port: " + table.getNumber("FeederMotor", -1));
         text.append('\n' + "Shooter Motor Port: " + table.getNumber("ShooterMotor", -1));
         text.append('\n' + "Climber Motor Port: " + table.getNumber("ClimberMotor", -1));
         text.append('\n' + "");
         text.append('\n' + "Left Analog Stick: " + table.getNumber("LeftAnalog", -1));
         text.append('\n' + "Right Analog Stick: " + table.getNumber("RightAnalog", -1));
         text.append('\n' + "Half Speed Toggle: " + table.getNumber("HalfSpeedToggle", -1));
         text.append('\n' + "Intake In Button: " + table.getNumber("IntakeInButton", -1));
         text.append('\n' + "Intake Out Button: " + table.getNumber("IntakeOutButton", -1));
         text.append('\n' + "Feeder Button: " + table.getNumber("FeederButton", -1));
         text.append('\n' + "Shooter Toggle: " + table.getNumber("ShooterToggle", -1));
         text.append('\n' + "Shooter Increase Speed POV: " + table.getNumber("ShooterIncreaseSpeed", -1));
         text.append('\n' + "Shooter Decrease Speed POV: " + table.getNumber("ShooterDecreaseSpeed", -1));
         text.append('\n' + "Climber Button: " + table.getNumber("ClimberButton", -1));*/
        text.append("Left Front Motor Port: " + LeftFrontMotor);
        text.append('\n' + "Left Back Motor Port: " + LeftBackMotor);
        text.append('\n' + "Right Front Motor Port: " + RightFrontMotor);
        text.append('\n' + "Right Back Motor Port: " + RightBackMotor);
        text.append('\n' + "Intake Motor Port: " + IntakeMotor);
        text.append('\n' + "Feeder Motor Port: " + FeederMotor);
        text.append('\n' + "Shooter Motor Port: " + ShooterMotor);
        text.append('\n' + "Climber Motor Port: " + ClimberMotor);
        text.append('\n' + "");
        text.append('\n' + "Left Analog Stick: " + LeftAnalog);
        text.append('\n' + "Right Analog Stick: " + RightAnalog);
        text.append('\n' + "Half Speed Toggle: " + HalfSpeedToggle);
        text.append('\n' + "Intake In Button: " + IntakeInButton);
        text.append('\n' + "Intake Out Button: " + IntakeOutButton);
        text.append('\n' + "Feeder Button: " + FeederButton);
        text.append('\n' + "Shooter Toggle: " + ShooterToggle);
        text.append('\n' + "Shooter Increase Speed POV: " + ShooterIncreaseSpeed);
        text.append('\n' + "Shooter Decrease Speed POV: " + ShooterDecreaseSpeed);
        text.append('\n' + "Climber Button: " + ClimberButton);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    public void run() {
        String directory = System.getProperty("user.home");
        String configFile = directory + "\\Desktop\\config.properties";
        System.out.println(configFile);
        String line = null;
        NetworkTable.setClientMode();
        NetworkTable.setTeam(1622);
        table = NetworkTable.getTable("ConfigTable");
        NetworkTablesClient client = new NetworkTablesClient();
        FileReader configRead = null;
        BufferedReader bufferedReader = null;
        try {
            configRead = new FileReader(configFile);
            bufferedReader = new BufferedReader(configRead);
            if (!bufferedReader.readLine().equals("##1622-SPYDER CONFIG 2017")) {
                FileWriter write = new FileWriter(configFile);
                //cedchiu@gmail.com
                BufferedWriter configWrite = new BufferedWriter(write);
                configWrite.write("##1622-SPYDER CONFIG 2017");
                configWrite.write('\n' + "##DO NOT EDIT THIS HEADER");
                configWrite.write('\n' + "##ALWAYS FORMAT ENTRIES WITH THE DEFAULT SPACING");
                configWrite.write('\n' + "##LIKE THIS: Sample Motor = 9");
                configWrite.write('\n' + "");
                configWrite.write('\n' + "##Motor Ports");
                configWrite.write('\n' + "Left Front Motor = 3");
                configWrite.write('\n' + "Left Back Motor = 4");
                configWrite.write('\n' + "Right Front Motor = 1");
                configWrite.write('\n' + "Right Back Motor = 2");
                configWrite.write('\n' + "Intake Motor = 6");
                configWrite.write('\n' + "Feeder Motor = 5");
                configWrite.write('\n' + "Shooter Motor = 8");
                configWrite.write('\n' + "Climber Motor = 7");
                configWrite.write('\n' + "");
                configWrite.write('\n' + "##Control Mapping:");
                configWrite.write('\n' + "Left Analog Stick = 1");
                configWrite.write('\n' + "Right Analog Stick = 3");
                configWrite.write('\n' + "Half Speed Toggle = 1");
                configWrite.write('\n' + "Intake In Button = 1");
                configWrite.write('\n' + "Intake Out Button = 4");
                configWrite.write('\n' + "Feeder Button = 6");
                configWrite.write('\n' + "Shooter Toggle = 5");
                configWrite.write('\n' + "Shooter Increase Speed POV = 0");
                configWrite.write('\n' + "Shooter Decrease Speed POV = 180");
                configWrite.write('\n' + "Climber Button = 3");
                configWrite.close();
            }
        } catch (Exception ex) {
        }
        while (true) {
            try {
                configRead = new FileReader(configFile);
                bufferedReader = new BufferedReader(configRead);
                while ((line = bufferedReader.readLine()) != null) {
                    if (line.contains("Left Front Motor")) {
                        LeftFrontMotor = Character.getNumericValue(line.charAt(19));
                    } else if (line.contains("Left Back Motor")) {
                        LeftBackMotor = Character.getNumericValue(line.charAt(18));
                    } else if (line.contains("Right Front Motor")) {
                        RightFrontMotor = Character.getNumericValue(line.charAt(20));
                    } else if (line.contains("Right Back Motor")) {
                        RightBackMotor = Character.getNumericValue(line.charAt(19));
                    } else if (line.contains("Intake Motor")) {
                        IntakeMotor = Character.getNumericValue(line.charAt(15));
                    } else if (line.contains("Feeder Motor")) {
                        FeederMotor = Character.getNumericValue(line.charAt(15));
                    } else if (line.contains("Shooter Motor")) {
                        ShooterMotor = Character.getNumericValue(line.charAt(16));
                    } else if (line.contains("Climber Motor")) {
                        ClimberMotor = Character.getNumericValue(line.charAt(16));
                    } else if (line.contains("Left Analog Stick")) {
                        LeftAnalog = Character.getNumericValue(line.charAt(20));
                    } else if (line.contains("Right Analog Stick")) {
                        RightAnalog = Character.getNumericValue(line.charAt(21));
                    } else if (line.contains("Half Speed Toggle")) {
                        HalfSpeedToggle = Character.getNumericValue(line.charAt(20));
                    } else if (line.contains("Intake In Button")) {
                        IntakeInButton = Character.getNumericValue(line.charAt(19));
                    } else if (line.contains("Intake Out Button")) {
                        IntakeOutButton = Character.getNumericValue(line.charAt(20));
                    } else if (line.contains("Feeder Button")) {
                        FeederButton = Character.getNumericValue(line.charAt(16));
                    } else if (line.contains("Shooter Toggle")) {
                        ShooterToggle = Character.getNumericValue(line.charAt(17));
                    } else if (line.contains("Shooter Increase Speed")) {
                        if (line.length() == 30) {
                            ShooterIncreaseSpeed = Character.getNumericValue(line.charAt(29));
                        } else if (line.length() == 31) {
                            int ones = Character.getNumericValue(line.charAt(30));
                            int tens = Character.getNumericValue(line.charAt(29)) * 10;
                            ShooterIncreaseSpeed = tens + ones;
                        } else if (line.length() == 32) {
                            int ones = Character.getNumericValue(line.charAt(31));
                            int tens = Character.getNumericValue(line.charAt(30)) * 10;
                            int hundreds = Character.getNumericValue(line.charAt(29)) * 100;
                            ShooterIncreaseSpeed = hundreds + tens + ones;
                        }
                    } else if (line.contains("Shooter Decrease Speed")) {
                        if (line.length() == 30) {
                            ShooterDecreaseSpeed = Character.getNumericValue(line.charAt(29));
                        } else if (line.length() == 31) {
                            int ones = Character.getNumericValue(line.charAt(30));
                            int tens = Character.getNumericValue(line.charAt(29)) * 10;
                            ShooterDecreaseSpeed = tens + ones;
                        } else if (line.length() == 32) {
                            int ones = Character.getNumericValue(line.charAt(31));
                            int tens = Character.getNumericValue(line.charAt(30)) * 10;
                            int hundreds = Character.getNumericValue(line.charAt(29)) * 100;
                            ShooterDecreaseSpeed = hundreds + tens + ones;
                        }
                    } else if (line.contains("Climber Button")) {
                        ClimberButton = Character.getNumericValue(line.charAt(17));
                    }
                }
            } catch (FileNotFoundException ex) {
                try {
                    FileWriter write = new FileWriter(configFile);
                    //cedchiu@gmail.com
                    BufferedWriter configWrite = new BufferedWriter(write);
                    configWrite.write("##1622-SPYDER CONFIG 2017");
                    configWrite.write('\n' + "##DO NOT EDIT THIS HEADER");
                    configWrite.write('\n' + "##ALWAYS FORMAT ENTRIES WITH THE DEFAULT SPACING");
                    configWrite.write('\n' + "##LIKE THIS: Sample Motor = 9");
                    configWrite.write('\n' + "");
                    configWrite.write('\n' + "##Motor Ports");
                    configWrite.write('\n' + "Left Front Motor = 3");
                    configWrite.write('\n' + "Left Back Motor = 4");
                    configWrite.write('\n' + "Right Front Motor = 1");
                    configWrite.write('\n' + "Right Back Motor = 2");
                    configWrite.write('\n' + "Intake Motor = 6");
                    configWrite.write('\n' + "Feeder Motor = 5");
                    configWrite.write('\n' + "Shooter Motor = 8");
                    configWrite.write('\n' + "Climber Motor = 7");
                    configWrite.write('\n' + "");
                    configWrite.write('\n' + "##Control Mapping:");
                    configWrite.write('\n' + "Left Analog Stick = 1");
                    configWrite.write('\n' + "Right Analog Stick = 3");
                    configWrite.write('\n' + "Half Speed Toggle = 1");
                    configWrite.write('\n' + "Intake In Button = 1");
                    configWrite.write('\n' + "Intake Out Button = 4");
                    configWrite.write('\n' + "Feeder Button = 6");
                    configWrite.write('\n' + "Shooter Toggle = 5");
                    configWrite.write('\n' + "Shooter Increase Speed POV = 0");
                    configWrite.write('\n' + "Shooter Decrease Speed POV = 180");
                    configWrite.write('\n' + "Climber Button = 3");
                    configWrite.close();
                } catch (IOException IOex) {
                }
            } catch (IOException ex) {
            }
            try {
                table.putNumber("LeftFrontMotor", LeftFrontMotor);
                table.putNumber("LeftBackMotor", LeftBackMotor);
                table.putNumber("RightFrontMotor", RightFrontMotor);
                table.putNumber("RightBackMotor", RightBackMotor);
                table.putNumber("IntakeMotor", IntakeMotor);
                table.putNumber("FeederMotor", FeederMotor);
                table.putNumber("ShooterMotor", ShooterMotor);
                table.putNumber("ClimberMotor", ClimberMotor);
                table.putNumber("LeftAnalog", LeftAnalog);
                table.putNumber("RightAnalog", RightAnalog);
                table.putNumber("HalfSpeedToggle", HalfSpeedToggle);
                table.putNumber("IntakeInButton", IntakeInButton);
                table.putNumber("IntakeOutButton", IntakeOutButton);
                table.putNumber("FeederButton", FeederButton);
                table.putNumber("ShooterToggle", ShooterToggle);
                table.putNumber("ShooterIncreaseSpeed", ShooterIncreaseSpeed);
                table.putNumber("ShooterDecreaseSpeed", ShooterDecreaseSpeed);
                table.putNumber("ClimberButton", ClimberButton);

                text.setText("");
                /*text.append('\n' + "Left Front Motor Port: " + table.getNumber("LeftFrontMotor", -1));
                 text.append('\n' + "Left Back Motor Port: " + table.getNumber("LeftBackMotor", -1));
                 text.append('\n' + "Right Front Motor Port: " + table.getNumber("RightFrontMotor", -1));
                 text.append('\n' + "Right Back Motor Port: " + table.getNumber("RightBackMotor", -1));
                 text.append('\n' + "Intake Motor Port: " + table.getNumber("IntakeMotor", -1));
                 text.append('\n' + "Feeder Motor Port: " + table.getNumber("FeederMotor", -1));
                 text.append('\n' + "Shooter Motor Port: " + table.getNumber("ShooterMotor", -1));
                 text.append('\n' + "Climber Motor Port: " + table.getNumber("ClimberMotor", -1));
                 text.append('\n' + "");
                 text.append('\n' + "Left Analog Stick: " + table.getNumber("LeftAnalog", -1));
                 text.append('\n' + "Right Analog Stick: " + table.getNumber("RightAnalog", -1));
                 text.append('\n' + "Half Speed Toggle: " + table.getNumber("HalfSpeedToggle", -1));
                 text.append('\n' + "Intake In Button: " + table.getNumber("IntakeInButton", -1));
                 text.append('\n' + "Intake Out Button: " + table.getNumber("IntakeOutButton", -1));
                 text.append('\n' + "Feeder Button: " + table.getNumber("FeederButton", -1));
                 text.append('\n' + "Shooter Toggle: " + table.getNumber("ShooterToggle", -1));
                 text.append('\n' + "Shooter Increase Speed POV: " + table.getNumber("ShooterIncreaseSpeed", -1));
                 text.append('\n' + "Shooter Decrease Speed POV: " + table.getNumber("ShooterDecreaseSpeed", -1));
                 text.append('\n' + "Climber Button: " + table.getNumber("ClimberButton", -1));*/
                text.append("Left Front Motor Port: " + LeftFrontMotor);
                text.append('\n' + "Left Back Motor Port: " + LeftBackMotor);
                text.append('\n' + "Right Front Motor Port: " + RightFrontMotor);
                text.append('\n' + "Right Back Motor Port: " + RightBackMotor);
                text.append('\n' + "Intake Motor Port: " + IntakeMotor);
                text.append('\n' + "Feeder Motor Port: " + FeederMotor);
                text.append('\n' + "Shooter Motor Port: " + ShooterMotor);
                text.append('\n' + "Climber Motor Port: " + ClimberMotor);
                text.append('\n' + "");
                text.append('\n' + "Left Analog Stick: " + LeftAnalog);
                text.append('\n' + "Right Analog Stick: " + RightAnalog);
                text.append('\n' + "Half Speed Toggle: " + HalfSpeedToggle);
                text.append('\n' + "Intake In Button: " + IntakeInButton);
                text.append('\n' + "Intake Out Button: " + IntakeOutButton);
                text.append('\n' + "Feeder Button: " + FeederButton);
                text.append('\n' + "Shooter Toggle: " + ShooterToggle);
                text.append('\n' + "Shooter Increase Speed POV: " + ShooterIncreaseSpeed);
                text.append('\n' + "Shooter Decrease Speed POV: " + ShooterDecreaseSpeed);
                text.append('\n' + "Climber Button: " + ClimberButton);

            } catch (Exception ex) {

            }
            try {
                Thread.sleep(1000);
            } catch (Exception ex) {
            }
        }
    }
}
