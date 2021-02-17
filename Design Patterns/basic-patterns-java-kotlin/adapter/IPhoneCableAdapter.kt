package adapter


class IPhoneCableAdapter(private val iphoneCable: IPhoneCable) : SamsungCable {
    override fun connectToSamsung(samsung: Samsung?) {
        println("Iphone Cable Adapter Connected to " + samsung!!.name)
        samsung.chargeSamsung()
    }
}