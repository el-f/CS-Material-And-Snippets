package adapter;

public class WhiteIPhoneCable implements IPhoneCable {

    @Override
    public void connectToIPhone(IPhone iphone) {
        System.out.println("Iphone Cable Connected to " + iphone.getName());
        iphone.chargeIPhone();
    }

}
