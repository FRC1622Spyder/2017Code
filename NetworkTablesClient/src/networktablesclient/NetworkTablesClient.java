package networktablesclient;

import java.io.*;
import edu.wpi.first.wpilibj.networktables.*;
import java.awt.FlowLayout;
import javax.swing.*;

public class NetworkTablesClient extends JFrame {
    //declares integers / for all the ports and mappings / to assign values
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
    int AutomaticDriveButton;
    int IntakeInButton; 
    int IntakeOutButton;
    int FeederButton;
    int ShooterToggle;
    int ShooterIncreaseSpeed;
    int ShooterDecreaseSpeed;
    int ClimberButton;

    //makes NetworkTable / to send values to robot / for ports and mappings
    NetworkTable table;

    //creates components / to be used in the window / so we can view things
    JFrame frame = new JFrame("ConfigTable 1622");
    static JTextArea text = new JTextArea(25, 40);
    static JScrollPane output = new JScrollPane(text, JScrollPane.VERTICAL_SCROLLBAR_NEVER, JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);

    public static void main(String[] args) {
        new NetworkTablesClient().run();
    }

    //designs the window / that will output the values / we get from config
    public NetworkTablesClient() {
        //regulates layout / and sets the size of window / and adds the text box
        frame.setLayout(new FlowLayout());
        frame.setSize(500, 500);
        frame.setResizable(false);
        frame.add(output);
        //user can't change text / also moves the window to / center of the screen
        text.setEditable(false);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        //program exits when / the output window is closed / because of reasons
        //including this one: / it runs infinitely if / we don't make it stop 
        frame.setDefaultCloseOperation(EXIT_ON_CLOSE);
        //adds text to text field / that shows us ports and mappings / so we can see them
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
        text.append('\n' + "Automatic Drive Button: " + AutomaticDriveButton);
        text.append('\n' + "Intake In Button: " + IntakeInButton);
        text.append('\n' + "Intake Out Button: " + IntakeOutButton);
        text.append('\n' + "Feeder Button: " + FeederButton);
        text.append('\n' + "Shooter Toggle: " + ShooterToggle);
        text.append('\n' + "Shooter Increase Speed POV: " + ShooterIncreaseSpeed);
        text.append('\n' + "Shooter Decrease Speed POV: " + ShooterDecreaseSpeed);
        text.append('\n' + "Climber Button: " + ClimberButton);
    }

    public void run() {
        //gets the location / of the file for the config / in user desktop
        String directory = System.getProperty("user.home");
        String configFile = directory + "\\Desktop\\config.properties";
        System.out.println(configFile);
        String line = null;
        //sets NetworkTable / as the client, not server / prepares to send stuff
        NetworkTable.setClientMode();
        NetworkTable.setTeam(1622);
        table = NetworkTable.getTable("ConfigTable");
        //creates an instance / of the visible window / so we can see it
        NetworkTablesClient client = new NetworkTablesClient();
        //reads the config / and checks the very first line / sees if it's screwed up
        FileReader configRead = null;
        BufferedReader bufferedReader = null;
        try {
            configRead = new FileReader(configFile);
            bufferedReader = new BufferedReader(configRead);
            //if first line is wrong / completely rewrite the file / as a precaution
            if (!bufferedReader.readLine().equals("##1622-SPYDER CONFIG 2017")) {
                FileWriter write = new FileWriter(configFile);
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
                configWrite.write('\n' + "Automatic Drive Button = 6");
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
        //updates the tables / this will run infinitely / 'til window is closed
        UpdateTables();
    }
    
    public void UpdateTables(){
        //sets variables / 'cuz they're not universal / and it's a new scope 
        String directory = System.getProperty("user.home");
        String configFile = directory + "\\Desktop\\config.properties";
        String line = null;
        FileReader configRead = null;
        BufferedReader bufferedReader = null;
        //loop the following / so that it keeps repeating / so values update
        while (true) {
            try {
                //update the values / from the configuration / file on the desktop
                //it reads through each line / and then retrieves some values / for ports and mappings
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
                    } else if (line.contains("Automatic Drive Button")) {
                        AutomaticDriveButton = Character.getNumericValue(line.charAt(25));
                    } else if (line.contains("Intake In Button")) {
                        IntakeInButton = Character.getNumericValue(line.charAt(19));
                    } else if (line.contains("Intake Out Button")) {
                        IntakeOutButton = Character.getNumericValue(line.charAt(20));
                    } else if (line.contains("Feeder Button")) {
                        FeederButton = Character.getNumericValue(line.charAt(16));
                    } else if (line.contains("Shooter Toggle")) {
                        ShooterToggle = Character.getNumericValue(line.charAt(17));
                    } else if (line.contains("Climber Button")) {
                        ClimberButton = Character.getNumericValue(line.charAt(17));
                    }
                    //these ones are special / could be two or three digits / so we change things up
                    //retrieves each digit / and strings them together as / multiples of ten 
                    else if (line.contains("Shooter Increase Speed")) {
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
                    }
                }
            }
            //error four oh four / if the file cannot be found / write out a new file
            catch (FileNotFoundException ex) {
                try {
                    FileWriter write = new FileWriter(configFile);
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
                    configWrite.write('\n' + "Automatic Drive Button = 6");
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
            //still in the while loop / so this will repeat itself / updates the table
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
                table.putNumber("AutomaticDriveButton", AutomaticDriveButton);
                table.putNumber("IntakeInButton", IntakeInButton);
                table.putNumber("IntakeOutButton", IntakeOutButton);
                table.putNumber("FeederButton", FeederButton);
                table.putNumber("ShooterToggle", ShooterToggle);
                table.putNumber("ShooterIncreaseSpeed", ShooterIncreaseSpeed);
                table.putNumber("ShooterDecreaseSpeed", ShooterDecreaseSpeed);
                table.putNumber("ClimberButton", ClimberButton);

                //updates the window / using the values that just / got sent to table
                text.setText("");
                text.append("Left Front Motor Port: " + (int) table.getNumber("LeftFrontMotor", -1));
                text.append('\n' + "Left Back Motor Port: " + (int) table.getNumber("LeftBackMotor", -1));
                text.append('\n' + "Right Front Motor Port: " + (int) table.getNumber("RightFrontMotor", -1));
                text.append('\n' + "Right Back Motor Port: " + (int) table.getNumber("RightBackMotor", -1));
                text.append('\n' + "Intake Motor Port: " + (int) table.getNumber("IntakeMotor", -1));
                text.append('\n' + "Feeder Motor Port: " + (int) table.getNumber("FeederMotor", -1));
                text.append('\n' + "Shooter Motor Port: " + (int) table.getNumber("ShooterMotor", -1));
                text.append('\n' + "Climber Motor Port: " + (int) table.getNumber("ClimberMotor", -1));
                text.append('\n' + "");
                text.append('\n' + "Left Analog Stick: " + (int) table.getNumber("LeftAnalog", -1));
                text.append('\n' + "Right Analog Stick: " + (int) table.getNumber("RightAnalog", -1));
                text.append('\n' + "Half Speed Toggle: " + (int) table.getNumber("HalfSpeedToggle", -1));
                text.append('\n' + "Automatic Drive Button: " + (int) table.getNumber("AutomaticDriveButton", -1));
                text.append('\n' + "Intake In Button: " + (int) table.getNumber("IntakeInButton", -1));
                text.append('\n' + "Intake Out Button: " + (int) table.getNumber("IntakeOutButton", -1));
                text.append('\n' + "Feeder Button: " + (int) table.getNumber("FeederButton", -1));
                text.append('\n' + "Shooter Toggle: " + (int) table.getNumber("ShooterToggle", -1));
                text.append('\n' + "Shooter Increase Speed POV: " + (int) table.getNumber("ShooterIncreaseSpeed", -1));
                text.append('\n' + "Shooter Decrease Speed POV: " + (int) table.getNumber("ShooterDecreaseSpeed", -1));
                text.append('\n' + "Climber Button: " + (int) table.getNumber("ClimberButton", -1));
                /*text.append("Left Front Motor Port: " + LeftFrontMotor);
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
                text.append('\n' + "Climber Button: " + ClimberButton);*/

            } catch (Exception ex) {

            }
            //waits for one second / so that constant refreshes / don't freeze the system
            try {
                Thread.sleep(1000);
            } catch (Exception ex) {
            }
        }
    }
}
