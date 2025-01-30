#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
///ADAM icin parametreler
#define BETA1 0.9
#define BETA2 0.999
///
#define IMAGE_SIZE 28
#define INPUT_SIZE (IMAGE_SIZE * IMAGE_SIZE) //28*28 = 784
#define NUM_CLASSES 4 /// 0 1 2 3
#define EPOCHS 50
#define LEARNING_RATE 0.01
#define EPSILON 1e-8 //cross entropy in log(0) cikmamasi icin 0 a yakin bir deger. log(0) tanimsiz oludgu icin kodu bozar

typedef struct {
    int label;//sinif
    double *pixels; /// pixeller
} ImageData;

typedef struct {
    double weights[INPUT_SIZE][NUM_CLASSES]; // 784*4 luk matris
    double biases[NUM_CLASSES];  //1*4 luk matris          
} Model;

///baslangic agirliklari
double initial_weights[INPUT_SIZE][NUM_CLASSES];
double initial_biases[NUM_CLASSES];

//rastgele agirliklarla modeli baslatma
void initialize_model(Model *model) {
    int i, j;
    for (i = 0; i < INPUT_SIZE; i++) {
        for (j = 0; j < NUM_CLASSES; j++) {
            model->weights[i][j] = ((double)rand() / RAND_MAX) * 0.01;
            initial_weights[i][j] = model->weights[i][j]; 
        }
    }
    for (j = 0; j < NUM_CLASSES; j++) {
        model->biases[j] = 0.0;
        initial_biases[j] = model->biases[j]; 
    }
}
//ayni baslangic agirlikalrini baska modelde de kullanmak icin kaydetme islemi
void reset_model(Model *model) {
    int i, j;
    for (i = 0; i < INPUT_SIZE; i++) {
        for (j = 0; j < NUM_CLASSES; j++) {
            model->weights[i][j] = initial_weights[i][j];
        }
    }
    for (j = 0; j < NUM_CLASSES; j++) {
        model->biases[j] = initial_biases[j];
    }
}

//verisetini yukleme
int load_data(const char *filename, ImageData **data_ptr, int *max_samples) {
	int i;
    FILE *file = fopen(filename, "r");
    
    int capacity = 2000;
    *data_ptr = (ImageData *)malloc(capacity * sizeof(ImageData));

    int count = 0;
    while (!feof(file)) {
        if (count >= capacity) {
            capacity *= 2;
            *data_ptr = (ImageData *)realloc(*data_ptr, capacity * sizeof(ImageData));
        }

        (*data_ptr)[count].pixels = (double *)malloc(INPUT_SIZE * sizeof(double));


        fscanf(file, "%d", &(*data_ptr)[count].label);
        for (i = 0; i < INPUT_SIZE; i++) {
            fscanf(file, "%lf", &(*data_ptr)[count].pixels[i]);
        }
        count++;
    }
    

    fclose(file);
    *max_samples = count;
    return count;
}


void free_data(ImageData *data, int count) {
	int i;
    for (i = 0; i < count; i++) {
        free(data[i].pixels);
    }
    free(data);
}
//loss fonksiyonu 
double cross_entropy_loss(double *predicted, int label) {
    return -log(predicted[label] + EPSILON);///epsilon log 0 tanýmsýz oldugu icin eklenmistir
}

/// aktivasyon fonksiyonu
void softmax(double *inputs, double *outputs, int size) {
    int i;
    double max_val = inputs[0];
    for (i = 1; i < size; i++) {
        if (inputs[i] > max_val) max_val = inputs[i];
    }

    double sum = 0.0;
    for (i = 0; i < size; i++) {
        outputs[i] = exp(inputs[i] - max_val);
        sum += outputs[i];
    }

    for (i = 0; i < size; i++) {
        outputs[i] /= sum;
    }
}

//burada modeli ve data yi aktivasyon fonksiyonunu sokup cikti aliyoruz
void forward(Model *model, double *input, double *output) {
    int i, j;
    double temp_output[NUM_CLASSES]; 

    for (j = 0; j < NUM_CLASSES; j++) {
        temp_output[j] = model->biases[j];
        for (i = 0; i < INPUT_SIZE; i++) {
            temp_output[j] += input[i] * model->weights[i][j];
        }
    }

    softmax(temp_output, output, NUM_CLASSES);
}

double evaluate_accuracy(Model *model, ImageData *data, int num_samples) {
	int n,j;
    int correct = 0;
    int predicted_label;
    for (n = 0; n < num_samples; n++) {
        double output[NUM_CLASSES];
        forward(model, data[n].pixels, output);//modelin cikti tahmin etmesi 

        predicted_label = 0;
        for (j = 1; j < NUM_CLASSES; j++) {
            if (output[j] > output[predicted_label]) {
                predicted_label = j;//en yuksek olasiliga sahip label i seciyoruz
            }
        }

        if (predicted_label == data[n].label) {
            correct++;
        }
    }
    return (double)correct / num_samples*100;
}


//Gradient Descent 
void train_gd(Model *model, ImageData *data, int num_samples, ImageData *test_data, int test_samples) {
    int i, j, n, epoch;
    double gradients[INPUT_SIZE][NUM_CLASSES]; ////Agirlik guncellemesinde kullancagimiz gradyanlar matrisi
    double bias_gradients[NUM_CLASSES];////bias guncellemesinde kullancagimiz gradyanlar matrisi
    double total_time = 0.0;
    struct timespec start_time, end_time;

    // Grafik cidirmek icin log dosyalarý
    FILE *file = fopen("train_gd.txt", "w");
    FILE *weights_file = fopen("weights_gd_1.txt", "w");
    ///epoch dongusu
    for (epoch = 0; epoch < EPOCHS; epoch++) {
    	
        clock_gettime(CLOCK_MONOTONIC, &start_time);
		//log dosyasýna yazdýrma islemleri 
        fprintf(weights_file, "Epoch %d:\n", epoch);
        for (i = 0; i < INPUT_SIZE; i++) {
            fprintf(weights_file, "w[%d]: ", i);
            for (j = 0; j < NUM_CLASSES; j++) {
                fprintf(weights_file, "%.6f ", model->weights[i][j]);
            }
            fprintf(weights_file, "\n");
        }
        ///gradyanlarý sifirlama islemi
        for (i = 0; i < INPUT_SIZE; i++) {
            for (j = 0; j < NUM_CLASSES; j++) {
                gradients[i][j] = 0.0;
            }
        }
        for (j = 0; j < NUM_CLASSES; j++) {
            bias_gradients[j] = 0.0;
        }

        double total_loss = 0.0;

        /// Tum veride iterasyon
        for (n = 0; n < num_samples; n++) {
            double output[NUM_CLASSES];
            // Model aðýrlýklarý ve veri kullanýlarak modelden cikti alinir.
            forward(model, data[n].pixels, output);

            // Kayýp hesabý
            total_loss += cross_entropy_loss(output, data[n].label);

            //Burada amac Loss fonskiyonunun turevini almak
            //Wi = Wi - a * dL/dWi ---> dL/dWi ---> (Si-1) * X burada Si softmax ciktisi X de data
            //Raporda daha detayli bahsettim
            double output_error[NUM_CLASSES];
            for (j = 0; j < NUM_CLASSES; j++) {
                output_error[j] = output[j] - (j == data[n].label ? 1 : 0);
            }

            // Gradyan hesabý (zincir kuralý)
            for (i = 0; i < INPUT_SIZE; i++) {
                for (j = 0; j < NUM_CLASSES; j++) {
                    gradients[i][j] += output_error[j] * data[n].pixels[i];
                }
            }
            for (j = 0; j < NUM_CLASSES; j++) {
                bias_gradients[j] += output_error[j];
            }
        }

        // Agirlik guncellemesi
        for (i = 0; i < INPUT_SIZE; i++) {
            for (j = 0; j < NUM_CLASSES; j++) {
            	//Wi = Wi - a * dL/dWi
            	
                model->weights[i][j] -= LEARNING_RATE * gradients[i][j] / num_samples;
                //burada num samples a bolerek gradyan ortalamasýna gore guncelleme yaptýk
            }
        }
        for (j = 0; j < NUM_CLASSES; j++) {
        	//Bi = Bi - a * dL/Bi
            model->biases[j] -= LEARNING_RATE * bias_gradients[j] / num_samples;
        }

        clock_gettime(CLOCK_MONOTONIC, &end_time); 

        double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + 
                              (end_time.tv_nsec - start_time.tv_nsec) / 1e9; // nanosaniye 
        total_time += elapsed_time;
        double train_accuracy = evaluate_accuracy(model, data, num_samples);
        double test_accuracy = evaluate_accuracy(model, test_data, test_samples);

        fprintf(file, "%d %.6f %.9f %.2f %.2f %.2f %.2f\n", epoch, total_loss / num_samples, elapsed_time, total_time, train_accuracy , test_accuracy);

        printf("Epoch %d: Loss = %f, Epoch Time = %.9fs, Total Time = %.2fs, Train Accuracy: %lf, Test Accuracy: %lf\n", 
               epoch, total_loss / num_samples, elapsed_time, total_time, train_accuracy , test_accuracy );
    }

    fclose(file);
    fclose(weights_file);
}



// Stochastic Gradient Descent 
void train_sgd(Model *model, ImageData *data, int num_samples,ImageData *test_data , int test_samples) {
    int epoch, i, j, k;
    double total_loss;
    const int batch_size = 64;//1 iterasyonda islenecek veri sayisi
    double total_time = 0.0;
    FILE *file = fopen("train_sgd.txt", "w");
    FILE *weights_file = fopen("weights_sgd_1.txt", "w");
    struct timespec start_time, end_time;

    
    for (epoch = 0; epoch < EPOCHS; epoch++) {
        clock_gettime(CLOCK_MONOTONIC, &start_time); 
        
        fprintf(weights_file, "Epoch %d:\n", epoch);
        for (i = 0; i < INPUT_SIZE; i++) {
            fprintf(weights_file, "w[%d]: ", i);
            for (j = 0; j < NUM_CLASSES; j++) {
                fprintf(weights_file, "%.6f ", model->weights[i][j]);
            }
            fprintf(weights_file, "\n");
        }
        double gradients[INPUT_SIZE][NUM_CLASSES] = {0};
        double bias_gradients[NUM_CLASSES] = {0};
        double total_loss = 0.0;

        // rastgele ornek secimi
        int indices[batch_size];
        for (k = 0; k < batch_size; k++) {
            indices[k] = rand() % num_samples;
            
        }
        //1 epcohta batch size kadar veri isleniyor
        for (k = 0; k < batch_size; k++) {
            int idx = indices[k];
            double output[NUM_CLASSES];
            forward(model, data[idx].pixels, output);

            //kayip hesabi
            total_loss += cross_entropy_loss(output, data[idx].label);
            // cikis katmani hatasi
            double output_error[NUM_CLASSES];
            for (j = 0; j < NUM_CLASSES; j++) {
                output_error[j] = output[j] - (j == data[idx].label ? 1 : 0);
            }

            // Gradyan hesabi zincir kurali
            for (i = 0; i < INPUT_SIZE; i++) {
                for (j = 0; j < NUM_CLASSES; j++) {
                    gradients[i][j] += output_error[j] * data[idx].pixels[i];
                }
            }
            for (j = 0; j < NUM_CLASSES; j++) {
                bias_gradients[j] += output_error[j];
            }
        }
        // Agirlik guncellemesi
        for (i = 0; i < INPUT_SIZE; i++) {
            for (j = 0; j < NUM_CLASSES; j++) {
                model->weights[i][j] -= LEARNING_RATE * gradients[i][j] / batch_size;//batch size kadar veri isledigimiz icin ortalamayi alýrken batch_size a bolduk
            }
        }
        for (j = 0; j < NUM_CLASSES; j++) {
            model->biases[j] -= LEARNING_RATE * bias_gradients[j] / batch_size;//batch size kadar veri isledigimiz icin ortalamayi alýrken batch_size a bolduk
        }

        
        clock_gettime(CLOCK_MONOTONIC, &end_time); 

        double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + 
                              (end_time.tv_nsec - start_time.tv_nsec) / 1e9; // nanosaniye 
        total_time += elapsed_time;
        
        double train_accuracy = evaluate_accuracy(model, data, num_samples);
        double test_accuracy = evaluate_accuracy(model, test_data, test_samples);
        fprintf(file, "%d %.6f %.9f %.2f %.2f %.2f %.2f\n", epoch, total_loss / batch_size, elapsed_time, total_time, train_accuracy , test_accuracy );

        printf("Epoch %d: Loss = %f, Epoch Time = %.9fs, Total Time = %.2fs, Train Accuracy: %lf, Test Accuracy: %lf\n", epoch, total_loss / batch_size, elapsed_time, total_time,train_accuracy,test_accuracy);
    }
    fclose(file);
    fclose(weights_file);
}


void train_adam(Model *model, ImageData *data, int num_samples,ImageData *test_data , int test_samples) {
    int epoch, i, j, n,k;
    const int batch_size = 64;
    double m[INPUT_SIZE][NUM_CLASSES] = {0};  // ilk moment vektoru
    double v[INPUT_SIZE][NUM_CLASSES] = {0};  // ikinci moment vektoru
    double m_bias[NUM_CLASSES] = {0};         // bias icin ilk moment
    double v_bias[NUM_CLASSES] = {0};         // bias icin ikinci moment
    double total_time = 0.0;
    FILE *file = fopen("train_adam.txt", "w");
    FILE *weights_file = fopen("weights_gd_adam_1.txt", "w");
    struct timespec start_time, end_time;

    for (epoch = 0; epoch < EPOCHS; epoch++) {
        clock_gettime(CLOCK_MONOTONIC, &start_time); 

        double total_loss = 0.0;
        //agirliklari dosyaya kaydet
        fprintf(weights_file, "Epoch %d:\n", epoch);
        for (i = 0; i < INPUT_SIZE; i++) {
            fprintf(weights_file, "w[%d]: ", i);
            for (j = 0; j < NUM_CLASSES; j++) {
                fprintf(weights_file, "%.6f ", model->weights[i][j]);
            }
            fprintf(weights_file, "\n");
        }
        //gradyan sifirlama
        double gradients[INPUT_SIZE][NUM_CLASSES] = {0};
        double bias_gradients[NUM_CLASSES] = {0};

        // batch_size kadar rastgele veri
        int indices[batch_size];
        for (k = 0; k < batch_size; k++) {
            indices[k] = rand() % num_samples; // Rastgele bir indeks seç
        }
        /// 1 epochta batch_size kadar veri islenir
        for (k = 0; k < batch_size; k++) {
            int idx = indices[k];

           
            double output[NUM_CLASSES];
            forward(model, data[idx].pixels, output);

            // kayip hesabi
            total_loss += cross_entropy_loss(output, data[idx].label);

            // cikis katmani hatasi
            double output_error[NUM_CLASSES];
            for (j = 0; j < NUM_CLASSES; j++) {
                output_error[j] = output[j] - (j == data[idx].label ? 1 : 0);
            }

            // gradyan hesabi zincir kurali 
            for (i = 0; i < INPUT_SIZE; i++) {
                for (j = 0; j < NUM_CLASSES; j++) {
                    gradients[i][j] += output_error[j] * data[idx].pixels[i];
                }
            }
            for (j = 0; j < NUM_CLASSES; j++) {
                bias_gradients[j] += output_error[j];
            }
        }

        // adam momenti ve agirliklarinin guncellenmesi
        for (i = 0; i < INPUT_SIZE; i++) {
            for (j = 0; j < NUM_CLASSES; j++) {
                double grad = gradients[i][j] / batch_size;

                m[i][j] = BETA1 * m[i][j] + (1 - BETA1) * grad;
                v[i][j] = BETA2 * v[i][j] + (1 - BETA2) * grad * grad;

                double m_hat = m[i][j] / (1 - pow(BETA1, epoch + 1));
                double v_hat = v[i][j] / (1 - pow(BETA2, epoch + 1));

                model->weights[i][j] -= LEARNING_RATE * m_hat / (sqrt(v_hat) + EPSILON);
            }
        }

        for (j = 0; j < NUM_CLASSES; j++) {
            double grad_bias = bias_gradients[j] / batch_size;

            m_bias[j] = BETA1 * m_bias[j] + (1 - BETA1) * grad_bias;
            v_bias[j] = BETA2 * v_bias[j] + (1 - BETA2) * grad_bias * grad_bias;

            double m_hat_bias = m_bias[j] / (1 - pow(BETA1, epoch + 1));
            double v_hat_bias = v_bias[j] / (1 - pow(BETA2, epoch + 1));

            model->biases[j] -= LEARNING_RATE * m_hat_bias / (sqrt(v_hat_bias) + EPSILON);
        }

        clock_gettime(CLOCK_MONOTONIC, &end_time); 

        double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + 
                              (end_time.tv_nsec - start_time.tv_nsec) / 1e9; // nanosaniye 
        total_time += elapsed_time;
        double train_accuracy = evaluate_accuracy(model, data, num_samples);
        double test_accuracy = evaluate_accuracy(model, test_data, test_samples);
        fprintf(file, "%d %.6f %.9f %.2f %.2f %.2f %.2f\n", epoch, total_loss / batch_size, elapsed_time, total_time, train_accuracy , test_accuracy );

        printf("Epoch %d: Loss = %f, Epoch Time = %.9fs, Total Time = %.2fs, Train Accuracy: %lf, Test Accuracy: %lf\n", epoch, total_loss / batch_size, elapsed_time, total_time,train_accuracy,test_accuracy);
    }
    fclose(file);
    fclose(weights_file);
}


int main() {
    srand(time(NULL));

    ImageData *train_data;
    ImageData *test_data;
    int train_samples, test_samples;

    //  veriseti 
    train_samples = load_data("train.txt", &train_data, &train_samples);
    test_samples = load_data("test.txt", &test_data, &test_samples);

    // model icin agirlik verme
    Model base_model;
    initialize_model(&base_model);

    // Gradient Descent ile egitim
    printf("\nGradient Descent ile Egitim Basliyor...\n");

    Model model_gd = base_model; 
    reset_model(&model_gd); //model agirliklarini baslangictaki agirliklara esitle 
    train_gd(&model_gd, train_data, train_samples,test_data,test_samples);

    // SGD ile egitim
    printf("\nSGD ile Egitim Basliyor...\n");

    Model model_sgd = base_model; 
    reset_model(&model_sgd); //model agirliklarini baslangictaki agirliklara esitle 
    train_sgd(&model_sgd, train_data, train_samples,test_data,test_samples);

    // Adam ile egitim
    printf("\nAdam ile Egitim Basliyor...\n");

    Model model_adam = base_model; 
    reset_model(&model_adam);
    train_adam(&model_adam, train_data, train_samples,test_data,test_samples);


    free_data(train_data, train_samples);
    free_data(test_data, test_samples);
    return 0;
}




