package adapter;

public class Tester {

    public static void main(String[] args) {
        IPhone iPhoneX = new IPhoneX();
        IPhoneCable whiteCable = new WhiteIPhoneCable();
        whiteCable.connectToIPhone(iPhoneX);

        Samsung s9 = new SamsungS9();
        IPhoneCableAdapter adapter = new IPhoneCableAdapter(whiteCable);
        adapter.connectToSamsung(s9);

    }

}
