package adapter


class WhiteIPhoneCable : IPhoneCable {
    override fun connectToIPhone(iphone: IPhone?) {
        println("Iphone Cable Connected to " + iphone!!.name)
        iphone.chargeIPhone()
    }
}