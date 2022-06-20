pipeline {
  agent any
  stages {
    stage('build') {
      steps {
        echo "Start building ..."
        sh 'make all'
      }
    }
    stage('deploy') {
      steps {
        echo "Deploying ..."
        echo "Done!"
      }
    }
  }
}
