import java.util.List;
import java.util.ArrayList;

/**
 * Write a description of class Field here.
 *
 * @author (your name)
 * @version (a version number or a date)
 */
public class Field
{
    private Object[][] field;

    public Field(int depth, int width) {
        field = new Object[depth][width];
    }

    public void clear(Location location) {
        field[location.getRow()][location.getCol()] = null;
    }

    public void place(Object obj, Location location) {
        field[location.getRow()][location.getCol()] = obj;
    }

    public int getDepth() {
        return field.length;
    }

    public int getWidth() {
        return field[0].length;
    }

    public Object getObjectAt(Location location) {
        return field[location.getRow()][location.getCol()];
    }

    public Location freeAdjacentLocation(Location location) {
        List<Location> free = new ArrayList<>();
        List<Location> adjacent = adjacentLocations(location);
        for (Location loc : adjacent) {
            if (getObjectAt(loc) == null) {
                free.add(loc);
            }
        }
        return free.isEmpty() ? null : free.get(0);
    }

    public List<Location> adjacentLocations(Location location) {
        List<Location> locations = new ArrayList<>();
        int row = location.getRow();
        int col = location.getCol();
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                int newRow = row + dr;
                int newCol = col + dc;
                if (newRow >= 0 && newRow < field.length && newCol >= 0 && newCol < field[0].length) {
                    locations.add(new Location(newRow, newCol));
                }
            }
        }
        return locations;
    }

    public void printField() {
        for (int row = 0; row < getDepth(); row++) {
            for (int col = 0; col < getWidth(); col++) {
                Object obj = field[row][col];
                if (obj == null) {
                    System.out.print(".");
                } else if (obj instanceof Rabbit) {
                    System.out.print("R");
                } else if (obj instanceof Fox) {
                    System.out.print("F");
                } else {
                    System.out.print("?");
                }
            }
            System.out.println();
        }
    }
}