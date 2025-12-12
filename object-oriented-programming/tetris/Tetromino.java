import java.awt.Color;
import java.util.Random;

public abstract class Tetromino {
    protected int[][] shape;
    protected int[][] originalShape;
    protected Color color;
    protected int colorValue;
    protected int x, y;
    private static Random random = new Random();

    public Tetromino(int[][] shape, Color color, int colorValue) {
        this.shape = shape;
        this.originalShape = copyArray(shape);
        this.color = color;
        this.colorValue = colorValue;
        this.x = 0;
        this.y = 0;
    }

    public static Tetromino createRandomTetromino() {
        int type = random.nextInt(7);
        return createTetrominoByType(type + 1);
    }

    public static Tetromino createTetrominoByType(int type) {
        switch (type) {
            case 1: return new IShape();
            case 2: return new OShape();
            case 3: return new TShape();
            case 4: return new LShape();
            case 5: return new JShape();
            case 6: return new SShape();
            case 7: return new ZShape();
            default: return new IShape();
        }
    }

    public void rotate() {
        int[][] rotated = new int[shape[0].length][shape.length];
        
        for (int y = 0; y < shape.length; y++) {
            for (int x = 0; x < shape[y].length; x++) {
                rotated[x][shape.length - 1 - y] = shape[y][x];
            }
        }
        
        shape = rotated;
    }

    public void rotateBack() {
        for (int i = 0; i < 3; i++) {
            rotate();
        }
    }

    public void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    public int[][] getShape() {
        return shape;
    }

    public Color getColor() {
        return color;
    }

    public int getColorValue() {
        return colorValue;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    private int[][] copyArray(int[][] arr) {
        int[][] copy = new int[arr.length][arr[0].length];
        for (int i = 0; i < arr.length; i++) {
            System.arraycopy(arr[i], 0, copy[i], 0, arr[i].length);
        }
        return copy;
    }
}

class IShape extends Tetromino {
    public IShape() {
        super(new int[][]{
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, new Color(0, 240, 240), 1);
    }
}

class OShape extends Tetromino {
    public OShape() {
        super(new int[][]{
            {2, 2},
            {2, 2}
        }, new Color(240, 240, 0), 2);
    }

    @Override
    public void rotate() {
        
    }
}

class TShape extends Tetromino {
    public TShape() {
        super(new int[][]{
            {0, 3, 0},
            {3, 3, 3},
            {0, 0, 0}
        }, new Color(160, 0, 240), 3);
    }
}

class LShape extends Tetromino {
    public LShape() {
        super(new int[][]{
            {0, 0, 4},
            {4, 4, 4},
            {0, 0, 0}
        }, new Color(240, 160, 0), 4);
    }
}

class JShape extends Tetromino {
    public JShape() {
        super(new int[][]{
            {5, 0, 0},
            {5, 5, 5},
            {0, 0, 0}
        }, new Color(0, 0, 240), 5);
    }
}

class SShape extends Tetromino {
    public SShape() {
        super(new int[][]{
            {0, 6, 6},
            {6, 6, 0},
            {0, 0, 0}
        }, new Color(0, 240, 0), 6);
    }
}

class ZShape extends Tetromino {
    public ZShape() {
        super(new int[][]{
            {7, 7, 0},
            {0, 7, 7},
            {0, 0, 0}
        }, new Color(240, 0, 0), 7);
    }
}