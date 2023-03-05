package mypackage;

public class Rectangle extends Graph {
    private int width;
    private int height;

    public Rectangle() {
        super();
        this.width = 0;
        this.height = 0;
    }

    public Rectangle(GraphType type, String name, Vec2d pos, int width, int height, Color color) {
        super(type, name, pos, color);
        this.width = width;
        this.height = height;
    }

    public float area() {
        return this.width * this.height;
    }

    public float width() {
        return this.width;
    }

    public float height() {
        return this.height;
    }
}
