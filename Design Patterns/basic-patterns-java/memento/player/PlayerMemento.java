package memento.player;

import java.time.LocalDate;

public class PlayerMemento implements Memento {

    private Player player;
    private String name;
    private int point;
    private int level;
    private LocalDate created;


    public PlayerMemento(Player p) {
        this.player = p;
        this.name = p.getName();
        this.point = p.getPoint();
        this.level = p.getLevel();
        this.created = LocalDate.now();
    }

    public String getName() {
        return name;
    }

    public int getPoint() {
        return point;
    }

    public int getLevel() {
        return level;
    }

    public LocalDate getCreated() {
        return created;
    }

    @Override
    public String toString() {
        return name + " " + created;
    }


    @Override
    public void load() {
        player.setLevel(level);
        player.setName(name);
        player.setPoint(point);
    }
}
