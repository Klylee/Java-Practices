package mypackage;

import java.io.File;
import java.io.FileNotFoundException;
import java.lang.ref.SoftReference;
import java.util.Scanner;
import java.util.Vector;

public class UI {
    private File file;

    public UI() {
    }

    public UI(String path) {
        file = new File(path);
        if (this.file.exists() == false) {
            System.out.println("file doesn't exist");
        }
    }

    private GraphType readType(Scanner str_scan) {
        String str;
        if (str_scan.hasNext()) {
            str = str_scan.next();
        } else
            return GraphType.NONETYPE;
        if (str.matches("rectangle"))
            return GraphType.RECTANGLE;
        else if (str.matches("circular"))
            return GraphType.CIRCULAR;
        else if (str.matches("triangle"))
            return GraphType.TRIANGLE;
        else
            return GraphType.NONETYPE;
    }

    private boolean readInfo(GraphType type, Scanner str_scan, SoftReference<Vector<Graph>> graphs) {
        String name;
        if (str_scan.hasNext()) {
            name = str_scan.next();
        } else
            return false;

        int count = 11;
        if (type == GraphType.RECTANGLE)
            count = 7;
        else if (type == GraphType.CIRCULAR)
            count = 6;

        int[] list = new int[count];
        float alpha;
        for (int i = 0; i < count; i++) {
            if (str_scan.hasNext()) {
                list[i] = str_scan.nextInt();
            } else
                return false;
        }
        if (str_scan.hasNext()) {
            alpha = str_scan.nextFloat();
        } else
            return false;

        if (type == GraphType.RECTANGLE)
            graphs.get().add(new Rectangle(type, name, new Vec2d(list[0], list[1]), list[2], list[3],
                    new Color(list[4], list[5], list[6], alpha)));
        else if (type == GraphType.CIRCULAR)
            graphs.get().add(new Circular(type, name, new Vec2d(list[0], list[1]), list[2],
                    new Color(list[3], list[4], list[5], alpha)));
        else
            graphs.get().add(new Triangle(type, name, new Vec2d(list[0], list[1]), new Vec2d(list[2], list[3]),
                    new Vec2d(list[4], list[5]),
                    new Vec2d(list[6], list[7]), new Color(list[8], list[9], list[10], alpha)));
        return true;
    }

    public boolean Parser(SoftReference<Vector<Graph>> graphs) {
        Scanner scan;
        try {
            scan = new Scanner(file);
        } catch (FileNotFoundException e) {
            System.out.println("file doesn't exist");
            return false;
        }
        while (scan.hasNextLine()) {
            String str_line = scan.nextLine();
            Scanner str_scan = new Scanner(str_line);

            GraphType type = readType(str_scan);

            if (type == GraphType.NONETYPE) {
                scan.close();
                str_scan.close();
                return false;
            }
            if (readInfo(type, str_scan, graphs) == false) {
                scan.close();
                str_scan.close();
                return false;
            }
            str_scan.close();
        }

        scan.close();
        return true;
    }
}
