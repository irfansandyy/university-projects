public class ClockDisplay {
    private NumberDisplay hours;
    private NumberDisplay minutes;
    private NumberDisplay seconds;
    private NumberDisplay milliseconds;
    private String displayString;

    public ClockDisplay() {
        hours = new NumberDisplay(24);
        minutes = new NumberDisplay(60);
        seconds = new NumberDisplay(60);
        milliseconds = new NumberDisplay(1000);
        updateDisplay();
    }

    public ClockDisplay(int hour, int minute, int second, int millisecond) {
        hours = new NumberDisplay(24);
        minutes = new NumberDisplay(60);
        seconds = new NumberDisplay(60);
        milliseconds = new NumberDisplay(1000);
        setTime(hour, minute, second, millisecond);
    }

    public void timeTick() {
        milliseconds.increment();
        if(milliseconds.getValue() == 0) {
            seconds.increment();
            if(seconds.getValue() == 0) {
                minutes.increment();
                if(minutes.getValue() == 0) {
                    hours.increment();
                }
            }
        }

        updateDisplay();
    }

    public void setTime(int hour, int minute, int second, int millisecond) {
        hours.setValue(hour);
        minutes.setValue(minute);
        seconds.setValue(second);
        milliseconds.setValue(millisecond);
        updateDisplay();
    }

    public String getTime() {
        return displayString;
    }

    private void updateDisplay() {
        displayString = hours.getDisplayValue() + ":" + minutes.getDisplayValue() + ":" + seconds.getDisplayValue() + ":" + milliseconds.getDisplayValue();
    }
}