import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.Timer;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.util.Locale;
import java.util.Random;

public class Clock {
    private JFrame frame;
    private JLabel label;
    private JLabel dateLabel;
    private JLabel tempLabel;
    private ClockDisplay clock;
    private boolean clockRunning = false;
    private TimerThread timerThread;
    private Timer dateTimer;
    private Random random;
    private int currentTemp = 0;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Clock());
    }

    public Clock() {
        makeFrame();
        clock = new ClockDisplay();
        initDateAndTempTimer();
    }

    private void start() {
        if(!clockRunning) {
            clockRunning = true;
            timerThread = new TimerThread();
            timerThread.start();
        }
    }

    private void stop() {
        clockRunning = false;
    }

    private void step() {
        clock.timeTick();
        label.setText(clock.getTime());
    }

    private void showAbout() {
        JOptionPane.showMessageDialog(frame, 
            "Clock Version 1.0\n" +
            "A simple interface for the 'Objects First' clock display project",
            "About Clock",
            JOptionPane.INFORMATION_MESSAGE);
    }

    private void quit() {
        System.exit(0);
    }

    private void makeFrame() {
        frame = new JFrame("Clock");
        JPanel contentPane = (JPanel) frame.getContentPane();
        contentPane.setBorder(new EmptyBorder(1, 60, 1, 60));
        makeMenuBar(frame);

        contentPane.setLayout(new BorderLayout(12, 12));

    JPanel centerPanel = new JPanel(new BorderLayout());
        centerPanel.setOpaque(false);

        label = new JLabel("00:00:00", SwingConstants.CENTER);
        Font displayFont = label.getFont().deriveFont(96.0f);
        label.setFont(displayFont);
    centerPanel.add(label, BorderLayout.CENTER);

        JPanel dateRow = new JPanel(new BorderLayout());
        dateRow.setOpaque(false);
        dateRow.setBorder(new EmptyBorder(12, 0, 0, 0));
        dateLabel = new JLabel("", SwingConstants.LEFT);
        tempLabel = new JLabel("", SwingConstants.RIGHT);
        Font infoFont = label.getFont().deriveFont(24.0f);
        dateLabel.setFont(infoFont);
        tempLabel.setFont(infoFont);
        dateRow.add(dateLabel, BorderLayout.WEST);
        dateRow.add(tempLabel, BorderLayout.EAST);
    centerPanel.add(dateRow, BorderLayout.SOUTH);

        contentPane.add(centerPanel, BorderLayout.CENTER);

        JPanel toolbar = new JPanel();
        toolbar.setLayout(new GridLayout(1, 0));

        JButton startButton = new JButton("Start");
        startButton.addActionListener(e -> start());
        toolbar.add(startButton);

        JButton stopButton = new JButton("Stop");
        stopButton.addActionListener(e -> stop());
        toolbar.add(stopButton);
        
        JButton stepButton = new JButton("Step");
        stepButton.addActionListener(e -> step());
        toolbar.add(stepButton);

        JPanel flow = new JPanel();
        flow.add(toolbar);

        contentPane.add(flow, BorderLayout.SOUTH);
        
        frame.pack();

        Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
        frame.setLocation(d.width/2 - frame.getWidth()/2, d.height/2 - frame.getHeight()/2);
        frame.setVisible(true);
    }

    private void initDateAndTempTimer() {
        random = new Random();
        updateDateAndTemp();
        dateTimer = new Timer(1000, e -> updateDateAndTemp());
        dateTimer.setInitialDelay(0);
        dateTimer.start();
    }

    private void updateDateAndTemp() {
        if (dateLabel == null || tempLabel == null) return;
        Locale idID = new Locale("id", "ID");
        String dateText = LocalDate.now().format(DateTimeFormatter.ofPattern("EEEE, d MMMM yyyy", idID));
        dateLabel.setText(capitalizeFirst(dateText));

        int sec = LocalTime.now().getSecond();
        if (sec == 0 || currentTemp == 0) {
            currentTemp = 24 + random.nextInt(9);
        }
        tempLabel.setText(currentTemp + "°C");
    }

    private String capitalizeFirst(String s) {
        if (s == null || s.isEmpty()) return s;
        return Character.toUpperCase(s.charAt(0)) + s.substring(1);
    }

    private void makeMenuBar(JFrame frame) {
        final int SHORTCUT_MASK = Toolkit.getDefaultToolkit().getMenuShortcutKeyMask();

        JMenuBar menuBar = new JMenuBar();
        frame.setJMenuBar(menuBar);

        JMenu menu;
        JMenuItem item;

        menu = new JMenu("File");
        menuBar.add(menu);

        item = new JMenuItem("About Clock");
        item.addActionListener(e -> showAbout());
        menu.add(item);

        menu.addSeparator();

        item = new JMenuItem("Quit");
        item.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Q, SHORTCUT_MASK));
        item.addActionListener(e -> quit());
        menu.add(item);
    }

    class TimerThread extends Thread {
        public void run() {
            while (clockRunning) {
                step();
                pause();
            }
        }

        private void pause() {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException exc) {

            }
        }
    }
}
