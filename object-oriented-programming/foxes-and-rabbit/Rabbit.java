
/**
 * Write a description of class Rabbit here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Rabbit extends Animal
{
    public Rabbit(Field field, Location location) {
        super(field, location);
    }

    @Override
    public void act(java.util.List<Animal> newAnimals) {
        if (isAlive()) {
            Location newLocation = getField().freeAdjacentLocation(getLocation());
            if (newLocation != null) {
                setLocation(newLocation);
            } else {
                setDead();
            }
        }
    }
}