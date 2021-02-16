package adapter;

public class IPhoneX implements IPhone {

    @Override
    public String getName() {
        return "IPhone X";
    }

    @Override
    public void chargeIPhone() {
        System.out.println(getName() + " is charging...");
    }

}
