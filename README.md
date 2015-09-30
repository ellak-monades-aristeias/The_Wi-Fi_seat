# The_Wi-Fi_seat
# Περιγραφή της Πρότασης

Το Wi-Fi seat είναι κάθισμα εξωτερικού χώρου με ενσωματωμένο router που δίνει ελεύθερη πρόσβαση στο διαδίκτυο. Το κάθισμα κατασκευάζεται από plexiglass και είναι φωτιζόμενο. Ο φωτισμός διαφοροποιείται ως προς το χρώμα και ως προς την ένταση. Το χρώμα διαφοροποιείται από έντονο κόκκινο εως πράσινο αποτυπώνοντας την ένταση του σήματος Wi-Fi στην περιοχή. Η ένταση του φωτισμού του καθίσματος ρυθμίζεται ανάλογα με την κίνηση. Αν περνάει κάποιος κοντά στο κάθισμα, η ένταση θα δυναμώνεi, αλλιώς θα είναι χαμηλή. Επιπλέον, η ένταση ρυθμίζεται ανάλογα με τον διάχυτο φωτισμό στην περιοχή.

Σκόπός της πρότασης είναι η δημιουργία ενός πόλου έλξης που θα ενθαρρύνει τη χρήση του δημόσιου χώρου από τους πολίτες, προσθέτοντας επιπλέον ασφάλεια μετά τη δύση του ηλίου (λόγω του φωτισμού), χωρίς να κοστίζει πολύ (λόγω της ρύθμισης της έντασης του φωτισμού).

Επιπλέον, με τη χρήση πολλών τέτοιων καθισμάτων σε διαφορετικά σημεία, δημιουργείται και ένα εικαστικό έργο που αποτυπώνει την ένταση του δικτύου WI-Fi της περιοχής. Έτσι οπτικοποιείται ένα πρόσθετο επίπεδο πληροφορίας που συνδέεται με το δομημένο περιβάλλον.

# Κατασκευή

Το κάθισμα έχει μορφή κωνικού πενταγώνου, με τη μικρή διάμετρο στη βάση. Aποτελείται από τρία διακριτά στοιχεία: τη βάση, το περίβλημα και τον εσωτερικό πυρήνα.

Η βάση κατασκευάζεται από μεταλλική γωνία 10x4cm, που βιδώνεται στο έδαφος με ειδικούς πείρους, και μεταλλική λάμα που εξέχει από την γωνία κατά 2cm, έτσι ώστε να υποδεχθεί το περίβλημα.

Το περίβλημα κατασκευάζεται από φύλλα plexiglass, πάχους 6mm. Ο εσωτερικός πυρήνας έχει ορθογωνικό σχήμα και κατασκευάζεται από κόντρα πλακέ θαλάσσης 4mm. Οι πλευρές του είναι δυνατόν να κατασκευάστουν σε CNC καθώς «κουμπώνουν» η μία μέσα στην άλλη. Στην εξωτερική του πλευρά του στερεώνονται ταινίες led. Στο εσωτερικό του τοποθετείται ο διακομιστής (router), η κεραία, ο σένσορας έντασης του σήματος wi-fi καθώς και η πλακέτα που θα ρυθμίζει το χρώμα και την ένταση του φωτός, τύπου Arduino.

# Σύνδεση Wi-Fi

Το Wi-Fi seat διατίθεται σε δύο εκδόσεις από άποψη συνδεσιμότητας στο διαδίκτυο (Internet). Η μια διαθέτει δρομολογητή (router) με δυνατότητα διασύνδεσης τύπου 4G LTE ή 3G και παρέχει αυτόνομη πρόσβαση. Η δεύτερη διαθέτει δρομολογητή με δυνατότητα διασύνδεσης με άλλους δρομολογητές για την δημιουργία δικτύου πλέγματος (mesh network).

Η πρώτη έκδοση με αυτόνομο internet θα χρησιμοποιεί έναν δρομολογητή (router) τύπου D-Link 4G LTE. Προτιμήθηκε αυτός ο τύπος σε σχέση με κάποια έκδοση δρομολογητή με ανοιχτό λογισμικό (όπως τα OpenWrt, DD-WRT και HyperWRT) καθώς δεν υπάρχει διαθεσιμότητα ώριμης ανοιχτής λύσης ασύρματης δικτύωσης με διασύνδεση 4G LTE. Εναλλακτικά μπορεί να χρησιμοποιηθεί δρομολογητής TP-Link TL-MR3020 με λογισμικό OpenWrt και 3G modem Huawei E367 (με δυνατότητα HSPA+). Με αυτόν το δικτυακό εξοπλισμό, το Wi-Fi seat μπορεί να εξυπηρετήσει έως 5-8 χρήστες.

Η δεύτερη έκδοση εξοπλίζεται με δρομολογητή Open-Mesh OM5P-AN Dual Band και δίνει την δυνατότητα για την δημιουργία ενός δικτύου πλέγματος (mesh network) με την διασύνδεση διαφορετικών Wi-Fi seats. Μπορεί να εγκατασταθεί σε σημεία όπου υπάρχει ασύρματη πρόσβαση διαθέσιμη από τον Δήμο. Έτσι δίνεται η δυνατότητα να επεκταθεί η κάλυψη του δικτύου πέρα από τα όρια που θέτει η εγκατάσταση σημείων ασύρματης πρόσβασης του Δήμου (Wifi hotspots). Η δημιουργία δικτύων πλέγματος (mesh networks) μπορεί να χρησιμοποιηθεί και χωρίς την πρόσβαση στο διαδίκτυο για τη δημιουργία μιας κοινότητας χρηστών που αξιοποιούν το δίκτυο για εφαρμογές όπως τα παιχνίδια (gaming), οι συνομιλίες (chat)και οι κλήσεις (VoIP).

# Έλεγχος έντασης και χρώματος φωτισμού

Πάνω στον εσωτερικό πυρήνα τοποθετούνται ταινίες LED. Περιμετρικά τοποθετούνται σένσορες κίνησης τύπου PIR (Passive Infrared" ή "Pyroelectric), οι οποίοι έχουν ακτίνα 180 μοίρες.

Ο έλεγχος της έντασης του σήματος και συνεπώς της φωτεινότητας επιτυγχάνεται με τη χρήση μικρής πλακέτας τύπου Arduino, η οποία τοποθετείται μέσα στον ξύλινο πυρήνα του καθίσματος και προγραμματίζεται με ελεύθερο λογισμικό. Οι σένσορες κίνησης στέλνουν σήμα στην πλακέτα, ή οποία με χρήση MOSFET τρανζίστορ επηρεάζει το ηλεκτρικό σήμα προς τις LED ταινίες.

Κατά τις περιόδους που οι σένσορες δεν εντοπίζουν κίνηση, οι φωτεινότητα θα μειώνεται και θα παραμένει σε χαμηλά επίπεδα για εξοικονόμηση ενέργειας. Μία συγγενής εφαρμογή βρίσκεται σήμερα ήδη σε πιλοτική φάση σε προάστιο της Κοπεγχάγης, όπου η ένταση του φωτισμού από στήλους στο δρόμο μειώνεται αισθητά όταν κίνηση οχημάτων δεν εντοπίζεται στο δρομό. Επιπλέον, στο arduino σύστημα τοποθετείται ειδικό; σένσορα φωτεινότητας προκειμένου να ρυθμίζεται η ένταση του φωτισμού όταν ο γενικός φωτισμός είναι σε υψηλά επίπεδα.

Ο φωτισμός διαφοροποιείται ως προς το χρώμα και ως προς την ένταση. Το χρώμα των Led διαφοροποιείται από έντονο κόκκινο εως πράσινο αποτυπώνοντας την ένταση του σήματος Wi-Fi στην περιοχή. Η λειτουργία αυτή ρυθμίζεται επίσης μέσω ειδικού σένσορα που συνδέεται στην πλακέτα Arduino.

Το κάθισμα θα συνδέεται με ηλεκτρικό ρεύμα από την κοντινότερη πηγή, σε συνεννόηση με τον Δήμο.

# Συντήρηση

Για τη συντήρηση, αφαιρείται το περίβλημα του καθίσματος με μία μόνο κρυφή βίδα.
