package berkesule;

import javax.swing.*;
import java.awt.*;
import java.util.Date;
import java.util.InputMismatchException;
import java.util.Random;
import java.util.Scanner;

public class Main {
    private static boolean isGuiMode = false; // Başlangıçta konsol modunda
    /*
    Patient alırken ad ve TC kimlik no alınıyor, Patinet ID rastgele 3 haneli bir sayı olarak atanıyor
     */
    public static void main(String[] args) {
        CRS crs = new CRS();
        
        String fullPath = "";
        crs.loadTablesToDisk(fullPath);

        
        Runnable mainTask = new Runnable() {
            @Override
            public void run() {
                while (true) {
                    synchronized (this) {
                        if (isGuiMode) {
                            launchGui(crs);
                        } else {
                            launchConsole(crs);
                        }
                    }
                }
            }
        };

        Thread mainThread = new Thread(mainTask);
        mainThread.start();
    }


    // Konsol modunu başlatır
    private synchronized static void launchConsole(CRS crs) {
        Scanner scanner = new Scanner(System.in);
        String fullPath = "";


        boolean mainMenuActive = true;
        while (mainMenuActive && !isGuiMode) {
            System.out.println("Giriş Tipi:");
            System.out.println("1. Kullanıcı Girişi");
            System.out.println("2. Yönetici Girişi");
            System.out.println("3. Bilgileri Yazdır");
            System.out.println("4. GUI Moduna Geç");
            System.out.println("5. Çıkış yap");
            System.out.print("Seçiminizi yapın (1-5): ");
            int userType = scanner.nextInt();

            switch (userType) {
                case 1:
                    handleUserMenu(scanner, crs);
                    break;
                case 2:
                    handleAdminMenu(scanner, crs);
                    break;
                case 3:
                    crs.printData();
                    break;
                case 4:
                    isGuiMode = true;
                    mainMenuActive = false;
                    
                    break;
                case 5:
                    System.out.println("Çıkış yapılıyor...");
                    mainMenuActive = false;
                    System.exit(0);
                    break;
                default:
                    System.out.println("Geçersiz seçim. Lütfen tekrar deneyin.");
            }
        }
        crs.saveTablesToDisk(fullPath);
    }

    // GUI modunu başlatır
    private synchronized static void launchGui(CRS crs) {
    	String fullPath = "";
        JFrame frame = new JFrame("Hospital Management System");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 1));

        JButton userButton = new JButton("Kullanıcı Girişi");
        JButton adminButton = new JButton("Yönetici Girişi");
        JButton printDataButton = new JButton("Bilgileri Yazdır");
        JButton consoleButton = new JButton("Konsol Moduna Geç");
        JButton exitButton = new JButton("Çıkış Yap");

        userButton.addActionListener(e -> handleUserGui(crs));
        adminButton.addActionListener(e -> handleAdminGui(crs));
        printDataButton.addActionListener(e -> JOptionPane.showMessageDialog(frame, crs.getAllData() ));
        consoleButton.addActionListener(e -> {
            isGuiMode = false;
            frame.dispose();
            
        });
        exitButton.addActionListener(e -> {
        crs.saveTablesToDisk(fullPath); 
        System.exit(0);
        });

        panel.add(userButton);
        panel.add(adminButton);
        panel.add(printDataButton);
        panel.add(consoleButton);
        panel.add(exitButton);

        frame.add(panel);
        frame.setVisible(true);
        while (isGuiMode) {
            try {
                Thread.sleep(100); 
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    @SuppressWarnings("unused")
	private static void handleUserGui(CRS crs) {
        JFrame frame = new JFrame("Kullanıcı İşlemleri");
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setSize(400, 200);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(3, 1));

        JButton addPatientButton = new JButton("Yeni Hasta Ekle");
        JButton appointmentButton = new JButton("Var olan Hasta ile Randevu Al");
        JButton backButton = new JButton("Geri Dön");

        addPatientButton.addActionListener(e -> {
            JTextField nameField = new JTextField();
            JTextField idField = new JTextField();

            Object[] message = {
                "Hasta Adı:", nameField,
                "Ulusal Kimlik Numarası:", idField
            };

            int option = JOptionPane.showConfirmDialog(frame, message, "Yeni Hasta Ekle", JOptionPane.OK_CANCEL_OPTION);
            if (option == JOptionPane.OK_OPTION) {
                try {
                    String name = nameField.getText();
                    String nationalIdText = idField.getText();
                    
                    if (nationalIdText.length() != 11 || !nationalIdText.matches("\\d+")) {
                        JOptionPane.showMessageDialog(frame, "Kimlik numarası 11 haneli bir sayı olmalıdır.");
                        return;
                    }

                    long nationalId = Long.parseLong(nationalIdText);
                    boolean exists = crs.getPatients().values().stream()
                            .anyMatch(patient -> patient.getNational_id() == nationalId);

                    if (exists) {
                        JOptionPane.showMessageDialog(frame, "Bu kimlik numarasıyla hasta zaten mevcut.");
                    } else {
                        long patientId = generateUniquePatientId(crs);
                        Patient newPatient = new Patient(name, nationalId);
                        crs.getPatients().put(patientId, newPatient);
                        JOptionPane.showMessageDialog(frame, "Hasta başarıyla eklendi. Hasta ID'si: " + patientId);
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Lütfen geçerli bir sayı giriniz.");
                }
            }
        });

        appointmentButton.addActionListener(e -> {
            JTextField patientIdField = new JTextField();
            JTextField patientNameField = new JTextField();
            JTextField nationalIdField = new JTextField();

            JComboBox<String> hospitalComboBox = new JComboBox<>();
            crs.getHospitals().values().forEach(hospital -> hospitalComboBox.addItem(hospital.getName()));

            JComboBox<String> sectionComboBox = new JComboBox<>();
            JComboBox<String> doctorComboBox = new JComboBox<>();

            hospitalComboBox.addActionListener(ev -> {
                sectionComboBox.removeAllItems();
                doctorComboBox.removeAllItems();

                Hospital selectedHospital = crs.getHospitals().values().stream()
                        .filter(h -> h.getName().equals(hospitalComboBox.getSelectedItem().toString()))
                        .findFirst().orElse(null);

                if (selectedHospital != null) {
                    selectedHospital.getSections().forEach(section -> sectionComboBox.addItem(section.getName()));
                }
            });

            sectionComboBox.addActionListener(ev -> {
                doctorComboBox.removeAllItems();

                Hospital selectedHospital = crs.getHospitals().values().stream()
                        .filter(h -> h.getName().equals(hospitalComboBox.getSelectedItem().toString()))
                        .findFirst().orElse(null);

                if (selectedHospital != null) {
                    Section selectedSection = selectedHospital.getSections().stream()
                            .filter(section -> section.getName().equals(sectionComboBox.getSelectedItem().toString()))
                            .findFirst().orElse(null);

                    if (selectedSection != null) {
                        selectedSection.getDoctors().forEach(doctor -> doctorComboBox.addItem(doctor.getName()));
                    }
                }
            });

            JSpinner dateSpinner = new JSpinner(new SpinnerDateModel());
            JSpinner.DateEditor dateEditor = new JSpinner.DateEditor(dateSpinner, "dd/MM/yyyy");
            dateSpinner.setEditor(dateEditor);

            Object[] message = {
                "Hasta ID:", patientIdField,
                "Hasta Adı:", patientNameField,
                "Ulusal Kimlik Numarası:", nationalIdField,
                "Hastane Seçimi:", hospitalComboBox,
                "Bölüm Seçimi:", sectionComboBox,
                "Doktor Seçimi:", doctorComboBox,
                "Tarih:", dateSpinner
            };

            int option = JOptionPane.showConfirmDialog(frame, message, "Randevu Al", JOptionPane.OK_CANCEL_OPTION);
            if (option == JOptionPane.OK_OPTION) {
                try {
                    long patientId = Long.parseLong(patientIdField.getText());
                    String patientName = patientNameField.getText();
                    String nationalIdText = nationalIdField.getText();

                    if (nationalIdText.length() != 11 || !nationalIdText.matches("\\d+")) {
                        JOptionPane.showMessageDialog(frame, "Kimlik numarası 11 haneli bir sayı olmalıdır.");
                        return;
                    }

                    long nationalId = Long.parseLong(nationalIdText);
                    String selectedHospitalName = hospitalComboBox.getSelectedItem().toString();
                    String selectedSectionName = sectionComboBox.getSelectedItem().toString();
                    String selectedDoctorName = doctorComboBox.getSelectedItem().toString();
                    Date selectedDate = (Date) dateSpinner.getValue();

                    Hospital selectedHospital = crs.getHospitals().values().stream()
                            .filter(h -> h.getName().equals(selectedHospitalName))
                            .findFirst().orElse(null);

                    if (selectedHospital != null) {
                        Section selectedSection = selectedHospital.getSections().stream()
                                .filter(section -> section.getName().equals(selectedSectionName))
                                .findFirst().orElse(null);

                        if (selectedSection != null) {
                            Doctor selectedDoctor = selectedSection.getDoctors().stream()
                                    .filter(doctor -> doctor.getName().equals(selectedDoctorName))
                                    .findFirst().orElse(null);

                            if (selectedDoctor != null) {
                                boolean appointmentCreated = crs.makeRandezvous(patientId, selectedHospital.getId(),
                                        selectedSection.getId(), selectedDoctor.getDiploma_id(), selectedDate);

                                if (appointmentCreated) {
                                    JOptionPane.showMessageDialog(frame, "Randevu başarıyla oluşturuldu.");
                                } else {
                                    JOptionPane.showMessageDialog(frame, "Seçilen doktorun o gün için hasta limiti dolu.");
                                }
                            } else {
                                JOptionPane.showMessageDialog(frame, "Doktor seçilemedi.");
                            }
                        } else {
                            JOptionPane.showMessageDialog(frame, "Bölüm seçilemedi.");
                        }
                    } else {
                        JOptionPane.showMessageDialog(frame, "Hastane seçilemedi.");
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Lütfen geçerli bir hasta ID giriniz.");
                }
            }
        });

        backButton.addActionListener(e -> frame.dispose());

        panel.add(addPatientButton);
        panel.add(appointmentButton);
        panel.add(backButton);

        frame.add(panel);
        frame.setVisible(true);
    }


    private static void handleAdminGui(CRS crs ) {
        JFrame frame = new JFrame("Yönetici İşlemleri");
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        frame.setSize(400, 300);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 1));

        JButton addHospitalButton = new JButton("Hastane Ekle");
        JButton addSectionButton = new JButton("Bölüm Ekle");
        JButton addDoctorButton = new JButton("Doktor Ekle");
        JButton backButton = new JButton("Geri Dön");

        addHospitalButton.addActionListener(e -> {
            JTextField nameField = new JTextField();
            JTextField idField = new JTextField();

            Object[] message = {
                "Hastane Adı:", nameField,
                "Hastane ID:", idField
            };

            int option = JOptionPane.showConfirmDialog(frame, message, "Hastane Ekle", JOptionPane.OK_CANCEL_OPTION);
            if (option == JOptionPane.OK_OPTION) {
                try {
                    String name = nameField.getText();
                    int hospitalId = Integer.parseInt(idField.getText());
                    if (crs.getHospitals().containsKey(hospitalId)) {
                        JOptionPane.showMessageDialog(frame, "Bu ID'ye sahip bir hastane zaten var.");
                    } else {
                        crs.getHospitals().put(hospitalId, new Hospital(hospitalId, name));
                        JOptionPane.showMessageDialog(frame, "Hastane başarıyla eklendi.");
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Lütfen geçerli bir hastane ID'si girin.");
                }
            }
        });

        addSectionButton.addActionListener(e -> {
            JComboBox<String> hospitalComboBox = new JComboBox<>();
            crs.getHospitals().values().forEach(hospital -> hospitalComboBox.addItem(hospital.getName()));

            JTextField sectionNameField = new JTextField();
            JTextField sectionIdField = new JTextField();

            Object[] message = {
                "Bölüm Adı:", sectionNameField,
                "Bölüm ID:", sectionIdField,
                "Hastane Seçimi:", hospitalComboBox
            };

            int option = JOptionPane.showConfirmDialog(frame, message, "Bölüm Ekle", JOptionPane.OK_CANCEL_OPTION);
            if (option == JOptionPane.OK_OPTION) {
                try {
                    String sectionName = sectionNameField.getText();
                    int sectionId = Integer.parseInt(sectionIdField.getText());
                    String selectedHospitalName = hospitalComboBox.getSelectedItem().toString();
                    Hospital selectedHospital = crs.getHospitals().values().stream()
                            .filter(h -> h.getName().equals(selectedHospitalName))
                            .findFirst()
                            .orElse(null);

                    if (selectedHospital != null) {
                    	try {
                            selectedHospital.addSection(new Section(sectionId, sectionName));
                            JOptionPane.showMessageDialog(frame, "Bölüm başarıyla eklendi.");
						} catch (DuplicateInfoException e2) {
							JOptionPane.showMessageDialog(frame, selectedHospitalName +"Hastanesinde zaten" + sectionId +"  ID sine sahip bölüm mevcut");
						}

                    } else {
                        JOptionPane.showMessageDialog(frame, "Hastane seçilemedi.");
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Lütfen geçerli bir bölüm ID'si girin.");
                }
            }
        });

        addDoctorButton.addActionListener(e -> {
            JComboBox<String> hospitalComboBox = new JComboBox<>();
            crs.getHospitals().values().forEach(hospital -> hospitalComboBox.addItem(hospital.getName()));

            JComboBox<String> sectionComboBox = new JComboBox<>();

            hospitalComboBox.addActionListener(ev -> {
                sectionComboBox.removeAllItems();
                String selectedHospitalName = hospitalComboBox.getSelectedItem().toString();
                Hospital selectedHospital = crs.getHospitals().values().stream()
                        .filter(h -> h.getName().equals(selectedHospitalName))
                        .findFirst()
                        .orElse(null);

                if (selectedHospital != null) {
                    selectedHospital.getSections().forEach(section -> sectionComboBox.addItem(section.getName()));
                }
            });

            JTextField doctorNameField = new JTextField();
            JTextField doctorIdField = new JTextField();
            JTextField diplomaIdField = new JTextField();
            JTextField maxPatientsField = new JTextField();

            Object[] message = {
                "Doktor Adı:", doctorNameField,
                "Kimlik ID:", doctorIdField,
                "Diploma ID:", diplomaIdField,
                "Günlük Hasta Limiti:", maxPatientsField,
                "Hastane Seçimi:", hospitalComboBox,
                "Bölüm Seçimi:", sectionComboBox
            };

            int option = JOptionPane.showConfirmDialog(frame, message, "Doktor Ekle", JOptionPane.OK_CANCEL_OPTION);
            if (option == JOptionPane.OK_OPTION) {
                try {
                    String doctorName = doctorNameField.getText();
                    long doctorNationalId = Long.parseLong(doctorIdField.getText());
                    int diplomaId = Integer.parseInt(diplomaIdField.getText());
                    int maxPatients = Integer.parseInt(maxPatientsField.getText());
                    String selectedHospitalName = hospitalComboBox.getSelectedItem().toString();
                    String selectedSectionName = sectionComboBox.getSelectedItem().toString();

                    Hospital selectedHospital = crs.getHospitals().values().stream()
                            .filter(h -> h.getName().equals(selectedHospitalName))
                            .findFirst()
                            .orElse(null);

                    Section selectedSection = selectedHospital != null ? selectedHospital.getSections().stream()
                            .filter(section -> section.getName().equals(selectedSectionName))
                            .findFirst()
                            .orElse(null) : null;

                    if (selectedSection != null) {
                    	try {
                            selectedSection.addDoctor(new Doctor(doctorName, doctorNationalId, diplomaId, maxPatients));
                            JOptionPane.showMessageDialog(frame, "Doktor başarıyla eklendi.");
						} catch (DuplicateInfoException e2) {
							JOptionPane.showMessageDialog(frame, selectedHospitalName +"Başarısız : bölümünde zaten bu doktor mevcut");
						}

                    } else {
                        JOptionPane.showMessageDialog(frame, "Bölüm seçilemedi.");
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Lütfen geçerli bir ID girin.");
                }
            }
        });

        backButton.addActionListener(e -> frame.dispose());

        panel.add(addHospitalButton);
        panel.add(addSectionButton);
        panel.add(addDoctorButton);
        panel.add(backButton);

        frame.add(panel);
        frame.setVisible(true);
    }


    //Konsol Modu İçin Kodlar:

    private static void handleUserMenu(Scanner scanner, CRS crs) {
        boolean userMenuActive = true;
        while (userMenuActive) {
            int choice = getIntInput(scanner, "Hasta işlemleri:\n1. Yeni hasta ekle\n2. Var olan hastayı seç ve randevu al\n3. Ana Menüye Dön\nSeçiminizi yapın (1, 2, veya 3): ");
            switch (choice) {
                case 1:
                    addNewPatient(scanner, crs);
                    break;
                case 2:
                    selectExistingPatient(scanner, crs);
                    break;
                case 3:
                    userMenuActive = false;
                    break;
                default:
                    System.out.println("Geçersiz seçim. Lütfen tekrar deneyin.");
            }
        }
    }

    private static void addNewPatient(Scanner scanner, CRS crs) {
        System.out.print("Yeni hasta adı: ");
        String name = scanner.nextLine();
        long nationalId = getLongInput(scanner, "Yeni hasta ulusal kimlik numarası: ");
        
        boolean exists = crs.getPatients().values().stream()
                .anyMatch(patient -> patient.getNational_id() == nationalId);

        if (exists) {
            System.out.println("Bu ulusal kimlik numarasına sahip bir hasta zaten mevcut. Yeni hasta eklenemedi.");
        } else {
            long patientId = generateUniquePatientId(crs);
            Patient newPatient = new Patient(name, nationalId);
            crs.getPatients().put(patientId, newPatient);
            System.out.println("Yeni hasta başarıyla eklendi: " + newPatient + " Hasta ID'si: " + patientId);
        }
    }

    private static long generateUniquePatientId(CRS crs) {
        Random random = new Random();
        long patientId;
        do {
            patientId = 100 + random.nextInt(900); // Generate a 3-digit ID
        } while (crs.getPatients().containsKey(patientId));
        return patientId;
    }

    private static void selectExistingPatient(Scanner scanner, CRS crs) {
        System.out.print("Hasta adı: ");
        String name = scanner.nextLine();
        long nationalId = getLongInput(scanner, "Hasta ulusal kimlik numarası: ");
        System.out.print("Hasta ID si: ");
        long patientId = scanner.nextLong();

        Patient existingPatient = crs.getPatients().get(patientId);
        if (existingPatient != null && existingPatient.getName().equalsIgnoreCase(name)
                && existingPatient.getNational_id() == nationalId) {
            System.out.println("Hasta doğrulandı: " + existingPatient);
            handlePatientRendezvous(scanner, crs, patientId);
        } else {
            System.out.println("Hasta bulunamadı veya bilgiler uyuşmuyor.");
        }
    }

    @SuppressWarnings("deprecation")
	private static void handlePatientRendezvous(Scanner scanner, CRS crs, long patientId) {
        System.out.println("Mevcut randevular:");
        crs.getRendezvous().stream()
                .filter(r -> r.getPatient().getNational_id() == crs.getPatients().get(patientId).getNational_id())
                .forEach(System.out::println);

        System.out.println("Randevu bilgilerinizi giriniz:");
        Hospital hospital = selectHospital(scanner, crs);
        Section section = selectSection(scanner, hospital);
        Doctor doctor = selectDoctor(scanner, section);

        boolean appointmentCreated = false;
        while (!appointmentCreated) {
            System.out.println("Randevu tarihi bilgilerini giriniz.");
            int year = getIntInput(scanner, "Yıl ");
            int month = getIntInput(scanner, "Ay");
            int day = getIntInput(scanner, "Gün ");
            try {
                Date date = new Date(year - 1900, month - 1, day);
                appointmentCreated = crs.makeRandezvous(patientId, hospital.getId(), section.getId(), doctor.getDiploma_id(), date);
                if (appointmentCreated) {
                    System.out.println("Randevu başarıyla oluşturuldu.");
                } else {
                    System.out.println("Seçilen doktorun o gün için hasta limiti dolu. Lütfen başka bir tarih seçin.");
                }
            } catch (Exception e) {
                System.out.println("Geçerli bir tarih giriniz.");
            }
        }
    }

    private static Hospital selectHospital(Scanner scanner, CRS crs) {
        while (true) {
            int hospitalId = getIntInput(scanner, "Hastane ID'si: ");
            Hospital hospital = crs.getHospitals().get(hospitalId);
            if (hospital != null) return hospital;
            System.out.println("Geçersiz hastane ID'si. Lütfen tekrar deneyin.");
        }
    }

    private static Section selectSection(Scanner scanner, Hospital hospital) {
        while (true) {
            int sectionId = getIntInput(scanner, "Bölüm ID'si: ");
            Section section = hospital.getSections().stream()
                    .filter(sec -> sec.getId() == sectionId)
                    .findFirst()
                    .orElse(null);
            if (section != null) return section;
            System.out.println("Geçersiz bölüm ID'si. Lütfen tekrar deneyin.");
        }
    }

    private static Doctor selectDoctor(Scanner scanner, Section section) {
        while (true) {
            int diplomaId = getIntInput(scanner, "Doktor diploma ID'si: ");
            Doctor doctor = section.getDoctors().stream()
                    .filter(doc -> doc.getDiploma_id() == diplomaId)
                    .findFirst()
                    .orElse(null);
            if (doctor != null) return doctor;
            System.out.println("Geçersiz doktor diploma ID'si. Lütfen tekrar deneyin.");
        }
    }

    private static void handleAdminMenu(Scanner scanner, CRS crs) {
        boolean adminMenuActive = true;
        while (adminMenuActive) {
            int choice = getIntInput(scanner, "Yönetici İşlemleri:\n1. Hastane Ekle\n2. Bölüm Ekle\n3. Doktor Ekle\n4. Ana Menüye Dön\nSeçiminizi yapın (1, 2, 3 veya 4): ");
            switch (choice) {
                case 1:
                    addHospital(scanner, crs);
                    break;
                case 2:
                    addSection(scanner, crs);
                    break;
                case 3:
                    addDoctor(scanner, crs);
                    break;
                case 4:
                    adminMenuActive = false;
                    break;
                default:
                    System.out.println("Geçersiz seçim. Lütfen tekrar deneyin.");
            }
        }
    }

    private static void addHospital(Scanner scanner, CRS crs) {
        System.out.print("Hastane adı: ");
        String name = scanner.nextLine();
        int id = getIntInput(scanner, "Hastane ID'si: ");

        if (crs.getHospitals().containsKey(id)) {
            System.out.println("Bu ID'ye sahip bir hastane zaten mevcut. Lütfen farklı bir ID giriniz.");
        } else {
            crs.getHospitals().put(id, new Hospital(id, name));
            System.out.println("Hastane başarıyla eklendi.");
        }
    }

    private static void addSection(Scanner scanner, CRS crs) {
        int hospitalId = getIntInput(scanner, "Hastane ID'si: ");
        Hospital hospital = crs.getHospitals().get(hospitalId);

        if (hospital != null) {
            System.out.print("Bölüm adı: ");
            String name = scanner.nextLine();
            int id = getIntInput(scanner, "Bölüm ID'si: ");
            try {
                hospital.addSection(new Section(id, name));
                System.out.println("Bölüm başarıyla eklendi.");
			} catch (DuplicateInfoException e) {
				System.out.println(e.getMessage());
			}

        } else {
            System.out.println("Hastane bulunamadı.");
        }
    }

    private static void addDoctor(Scanner scanner, CRS crs) {
        int hospitalId = getIntInput(scanner, "Hastane ID'si: ");
        Hospital hospital = crs.getHospitals().get(hospitalId);

        if (hospital != null) {
            int sectionId = getIntInput(scanner, "Bölüm ID'si: ");
            Section section = hospital.getSections().stream()
                    .filter(sec -> sec.getId() == sectionId)
                    .findFirst()
                    .orElse(null);

            if (section != null) {
                System.out.print("Doktor adı: ");
                String name = scanner.nextLine();
                long nationalId = getLongInput(scanner, "Kimlik ID'si: ");
                int diplomaId = getIntInput(scanner, "Diploma ID'si: ");
                int maxPatients = getIntInput(scanner, "Günlük hasta limiti: ");
                try {
                    section.addDoctor(new Doctor(name, nationalId, diplomaId, maxPatients));
                    System.out.println("Doktor başarıyla eklendi.");
				} catch (DuplicateInfoException e) {
					System.out.println(e.getMessage());
				}

            } else {
                System.out.println("Bölüm bulunamadı.");
            }
        } else {
            System.out.println("Hastane bulunamadı.");
        }
    }

    private static int getIntInput(Scanner scanner, String prompt) {
        while (true) {
            try {
                System.out.print(prompt);
                int input = scanner.nextInt();
                scanner.nextLine(); 
                return input;
            } catch (InputMismatchException e) {
                System.out.println("Geçerli bir sayı giriniz.");
                scanner.nextLine(); 
            }
        }
    }

    private static long getLongInput(Scanner scanner, String prompt) {
        while (true) {
            try {
                System.out.print(prompt);
                long input = scanner.nextLong();
                scanner.nextLine();
                if (String.valueOf(input).length() == 11) return input;
                System.out.println("Kimlik numarası 11 haneli olmalıdır.");
            } catch (InputMismatchException e) {
                System.out.println("Geçerli bir sayı giriniz.");
                scanner.nextLine();
            }
        }
    }


}
