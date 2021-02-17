package adapter;

public class SamsungS9 implements Samsung {

    @Override
    public String getName() {
        return "Samsung S9";
    }

    @Override
    public void chargeSamsung() {
        System.out.println(getName() + " is charging...");
    }

}
