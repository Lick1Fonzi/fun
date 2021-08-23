import pywhatkit

ora =int( input("inserisci ora") )
minuto =int( input("inserisci minuto") )
mes1 = "Gentile reminder delle "
mes2 = ": torna al nido presto, hai la nostra pizza"
cell = "+39775643676"	#example number
while(1):
	print("invio messaggio in attesa")
	#whatsapp web must be open for the message to be sent
	pywhatkit.sendwhatmsg(cell, mes1+str(ora)+" e "+str(minuto)+mes2, ora,minuto)
	print("messaggio inviato")
	minuto+=5
	if(minuto==60):
		ora+=1
		minuto=0;
