package mypackage;

public class Circular extends Graph {
    private int radius;

    public Circular() {
        super();
        radius = 0;
    }

    public Circular(GraphType type, String name, Vec2d pos, int radius, Color color) {
        super(type, name, pos, color);
        this.radius = radius;
    }

    public int radius() {
        return radius;
    }

    public float area() {
        return this.radius * this.radius * (float) Math.PI;
    }
}
