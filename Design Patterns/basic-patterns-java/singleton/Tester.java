package singleton;


public class Tester {
    public static void main(String[] args) {
        IdGenerator idGen = IdGenerator.getInstance(0);
        System.out.println("IDGen Next Id: " + idGen.getNext());
        System.out.println("IDGen Next Id: " + idGen.getNext());


        IdGenerator idGen2 = IdGenerator.getInstance(1);
        System.out.println("IDGen2 Next Id: " + idGen2.getNext());
        System.out.println("IDGen2 Next Id: " + idGen2.getNext());

        IdGenerator idGen3 = IdGenerator.getInstance(0);
        System.out.println("IDGen3 Next Id: " + idGen3.getNext());
        System.out.println("IDGen3 Next Id: " + idGen3.getNext());
    }
}

