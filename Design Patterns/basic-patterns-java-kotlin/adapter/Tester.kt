package adapter


fun main() {
    val iPhoneX: IPhone = IPhoneX()
    val whiteCable: IPhoneCable = WhiteIPhoneCable()
    whiteCable.connectToIPhone(iPhoneX)

    val s9: Samsung = SamsungS9()
    val adapter = IPhoneCableAdapter(whiteCable)
    adapter.connectToSamsung(s9)
}
