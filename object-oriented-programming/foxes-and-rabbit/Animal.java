
/**
 * Write a description of class Animal here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public abstract class Animal
{
    private int age;
    private boolean alive;
    private Field field;
    private Location location;

    public Animal(Field field, Location location) {
        age = 0;
        alive = true;
        this.field = field;
        setLocation(location);
    }

    public boolean isAlive() {
        return alive;
    }

    public void setDead() {
        alive = false;
        if(location != null) {
            field.clear(location);
            location = null;
            field = null;
        }
    }

    public Field getField() {
        return field;
    }

    public Location getLocation() {
        return location;
    }

    public void setLocation(Location newLocation) {
        if(location != null) {
            field.clear(location);
        }

        location = newLocation;
        field.place(this, newLocation);
    }

    public abstract void act(java.util.List<Animal> newAnimals);
}