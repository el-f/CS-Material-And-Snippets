package adapter;

public class IPhoneCableAdapter implements SamsungCable {
    private IPhoneCable iphoneCable;

    public IPhoneCableAdapter(IPhoneCable iphoneCable) {
        this.iphoneCable = iphoneCable;
    }

    @Override
    public void connectToSamsung(Samsung samsung) {
        System.out.println("Iphone Cable Adapter Connected to " + samsung.getName());
        samsung.chargeSamsung();
    }

}
