package memento;

public class Player implements Originator {

    private String name;
    private int point;
    private int level;

    public Player(String name) {
        this.name = name;
        this.point = 0;
        this.level = 1;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getPoint() {
        return point;
    }

    public void setPoint(int point) {
        this.point = point;
    }

    public int getLevel() {
        return level;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    @Override
    public String toString() {
        return "Player [name=" + name + ", point=" + point + ", level=" + level + "]";
    }


    @Override
    public Memento save() {
        return new PlayerMemento(this);
    }
}
