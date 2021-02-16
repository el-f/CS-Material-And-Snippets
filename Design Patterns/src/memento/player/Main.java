package memento.player;

public class Main {

    public static void main(String[] args) {
        CareTaker ct = new CareTaker();
        Player p = new Player("Yosi");
        Player p2 = new Player("Mosher");
        System.out.println(p);

        p.setLevel(5);
        p.setPoint(1000);
        ct.save(p.save());
        System.out.println(p);

        p2.setLevel(3);
        p2.setPoint(500);
        ct.save(p2.save());
        System.out.println(p2);

        System.out.println(ct);

        p.setLevel(5);
        p.setPoint(800);
        System.out.println(p);

        ct.load(0);
        System.out.println(p);
    }

}
